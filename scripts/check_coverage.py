#!/usr/bin/env python3
"""Build the Cerys project with coverage instrumentation and enforce coverage thresholds.

Usage:
    python scripts/check_coverage.py              # default thresholds (90% line, 90% branch)
    python scripts/check_coverage.py --strict     # 100% line, 100% branch
    python scripts/check_coverage.py --line 80 --branch 70
"""

from __future__ import annotations

import argparse
import os
import platform
import shutil
import subprocess
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
BUILD_DIR = REPO_ROOT / "build" / "coverage"

DEFAULT_LINE_THRESHOLD = 90.0
DEFAULT_BRANCH_THRESHOLD = 90.0
STRICT_LINE_THRESHOLD = 100.0
STRICT_BRANCH_THRESHOLD = 100.0


def run(cmd: list[str], cwd: Path) -> None:
    print(f"\n>>> {' '.join(cmd)}")
    result = subprocess.run(cmd, cwd=cwd)
    if result.returncode != 0:
        sys.exit(result.returncode)


def detect_generator() -> list[str]:
    if platform.system() == "Windows":
        for gen in ("Ninja", "NMake Makefiles", "Visual Studio 17 2022"):
            return ["-G", gen]
    return ["-G", "Ninja"]


def coverage_flags() -> list[str]:
    flags = "--coverage -fprofile-arcs -ftest-coverage -fbranch-probabilities"
    return [
        f"-DCMAKE_CXX_FLAGS={flags}",
        f"-DCMAKE_C_FLAGS={flags}",
        "-DCMAKE_EXE_LINKER_FLAGS=--coverage",
        "-DCMAKE_SHARED_LINKER_FLAGS=--coverage",
    ]


def find_gcov() -> str:
    for name in ("gcov", "gcov-12", "gcov-11", "gcov-10"):
        path = shutil.which(name)
        if path:
            return path
    sys.stderr.write("Error: gcov was not found on PATH. Install gcc/clang with gcov.\n")
    sys.exit(1)


def parse_gcov(path: Path) -> tuple[int, int, int, int]:
    """Return (lines_executed, lines_total, branches_executed, branches_total) from a .gcov file."""
    executed = total = branches_hit = branches_total = 0
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        if line.startswith("branch"):
            parts = line.split()
            if len(parts) < 4:
                continue
            try:
                taken = int(parts[3])
                branches_total += int(parts[2]) + 1
                branches_hit += taken
            except ValueError:
                pass
            continue
        head = line.split(":", 1)[0].strip()
        if not head.lstrip("-").isdigit():
            continue
        count = int(head)
        if "-" in head:
            continue
        total += 1
        if count > 0:
            executed += 1
    return executed, total, branches_hit, branches_total


def collect_coverage(gcov_root: Path, source_roots: list[Path], gcov_bin: str) -> dict[str, tuple[int, int, int, int]]:
    subprocess.run([gcov_bin, "--branch-counts", "--branch-probabilities", "--no-output",
                    "--preserve-paths", "-r", str(REPO_ROOT)],
                   cwd=gcov_root, capture_output=True)
    results: dict[str, tuple[int, int, int, int]] = {}
    for path in gcov_root.rglob("*.gcov"):
        try:
            rel = path.relative_to(gcov_root)
            original = str(rel).rsplit(".gcov", 1)[0]
            if not any(Path(original).is_relative_to(root) for root in source_roots):
                continue
            results[str(rel)] = parse_gcov(path)
        except ValueError:
            continue
    return results


def main() -> int:
    parser = argparse.ArgumentParser(description="Build and report Cerys coverage.")
    parser.add_argument("--line", type=float, default=DEFAULT_LINE_THRESHOLD,
                        help=f"Minimum line coverage percent (default: {DEFAULT_LINE_THRESHOLD}).")
    parser.add_argument("--branch", type=float, default=DEFAULT_BRANCH_THRESHOLD,
                        help=f"Minimum branch coverage percent (default: {DEFAULT_BRANCH_THRESHOLD}).")
    parser.add_argument("--strict", action="store_true",
                        help=f"Require 100%% line and 100%% branch coverage.")
    parser.add_argument("--build-dir", type=Path, default=BUILD_DIR,
                        help=f"Build directory (default: {BUILD_DIR}).")
    args = parser.parse_args()

    if args.strict:
        args.line = STRICT_LINE_THRESHOLD
        args.branch = STRICT_BRANCH_THRESHOLD

    build_dir = args.build_dir.resolve()
    if build_dir.exists():
        shutil.rmtree(build_dir)
    build_dir.mkdir(parents=True)

    run(["cmake", "-S", str(REPO_ROOT), "-B", str(build_dir),
         *detect_generator(), "-DCMAKE_BUILD_TYPE=Debug",
         "-DCERYS_BUILD_TESTS=ON", *coverage_flags()], cwd=REPO_ROOT)
    run(["cmake", "--build", str(build_dir), "--config", "Debug"], cwd=REPO_ROOT)

    if shutil.which("ctest"):
        run(["ctest", "--test-dir", str(build_dir), "--output-on-failure"], cwd=REPO_ROOT)
    else:
        print("ctest not found; skipping test execution.")

    gcov_bin = find_gcov()
    gcov_root = build_dir / "gcov"
    gcov_root.mkdir(exist_ok=True)

    source_roots = [REPO_ROOT / "src" / "core", REPO_ROOT / "tests"]
    results = collect_coverage(gcov_root, source_roots, gcov_bin)

    if not results:
        sys.stderr.write("Error: no coverage data was generated.\n")
        return 1

    total_lines = total_executed = total_branches = total_branches_hit = 0
    print(f"\n{'File':<70} {'Lines':>14} {'Branches':>14}")
    print(f"{'-' * 70} {'-' * 14} {'-' * 14}")
    for name, (executed, lines, b_hit, b_total) in sorted(results.items()):
        line_pct = (executed / lines * 100.0) if lines else 100.0
        branch_pct = (b_hit / b_total * 100.0) if b_total else 100.0
        print(f"{name:<70} {f'{executed}/{lines} ({line_pct:5.1f}%)':>14} "
              f"{f'{b_hit}/{b_total} ({branch_pct:5.1f}%)':>14}")
        total_executed += executed
        total_lines += lines
        total_branches_hit += b_hit
        total_branches += b_total

    line_pct = (total_executed / total_lines * 100.0) if total_lines else 0.0
    branch_pct = (total_branches_hit / total_branches * 100.0) if total_branches else 0.0

    print(f"\nOverall line coverage:    {total_executed}/{total_lines} ({line_pct:.1f}%)")
    print(f"Overall branch coverage:  {total_branches_hit}/{total_branches} ({branch_pct:.1f}%)")
    print(f"Thresholds:               line >= {args.line}%, branch >= {args.branch}%")

    failed = line_pct < args.line or branch_pct < args.branch
    if failed:
        print("\nFAIL: coverage thresholds not met.")
        return 1
    print("\nPASS: coverage thresholds met.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
