#!/usr/bin/env python3
"""Usage: python dev/tools/run_coverage.py [LINE%] [BRANCH%]
Positional thresholds default to 100/90. Reports land in build/."""
import os, subprocess, sys
from pathlib import Path

argv = sys.argv[1:]
positionals = [a for a in argv if not a.startswith("-")]
flags = [a for a in argv if a.startswith("-")]
line_th = float(positionals[0]) if len(positionals) >= 1 else 100.0
branch_th = float(positionals[1]) if len(positionals) >= 2 else 90.0
no_build = "--no-build" in flags
no_test = "--no-test" in flags

def argval(name, default):
    if name in flags:
        i = flags.index(name)
        if i + 1 < len(flags):
            return flags[i + 1]
    return default

build_dir = Path(argval("--build-dir", "build"))
report_prefix = Path(argval("--report", "coverage_report"))

project = Path(__file__).resolve().parent.parent.parent
build_dir = (project / build_dir).resolve()
report_xml = build_dir / report_prefix.with_suffix(".xml").name
report_html = build_dir / report_prefix.with_suffix(".html").name
report_txt = build_dir / report_prefix.with_suffix(".txt").name

def sh(cmd, cwd=None):
    print(f"\n$ {' '.join(str(c) for c in cmd)}")
    return subprocess.run(cmd, cwd=cwd, text=True, encoding="utf-8", errors="replace")

def die(msg, code=1):
    print(f"\n[FAIL] {msg}", file=sys.stderr); sys.exit(code)

if not no_build:
    cfg = ["cmake", "-S", str(project), "-B", str(build_dir),
           "-DCMAKE_BUILD_TYPE=Debug", "-DCERYS_COVERAGE=ON"]
    if subprocess.run(["where", "ninja"], capture_output=True).returncode == 0:
        cfg.append("-DCMAKE_GENERATOR=Ninja")
    if sh(cfg).returncode != 0: die("configure failed")
    if sh(["ninja", "core_tests"], cwd=build_dir).returncode != 0: die("build failed")

if not no_test:
    exe = build_dir / "tests" / "core" / ("core_tests.exe" if os.name == "nt" else "core_tests")
    rc = sh([str(exe)]).returncode
    if rc != 0: print(f"[warn] tests exit {rc}", file=sys.stderr)

src_root = str(project / "src").replace("\\", "/")
gcovr_cmd = [
    sys.executable, "-m", "gcovr",
    "--root", str(build_dir).replace("\\", "/"),
    "--filter", src_root + "/core/.*",
    "--filter", src_root + "/cpp/.*",
    "--xml", str(report_xml),
    "--html-details", str(report_html),
    "--txt", str(report_txt),
    "--print-summary",
    "--exclude-throw-branches",
    "--exclude-unreachable-branches",
    # Exclude unreachable throw lines in [[noreturn]] functions
    "--exclude-lines-by-pattern", r'^\s*throw\s+.*;',
    # Exclude function definition lines to handle compiler-generated template instantiations
    "--exclude-function-lines",
    "--fail-under-line", str(line_th),
    "--fail-under-branch", str(branch_th),
]
result = sh(gcovr_cmd, cwd=build_dir)

print("\n" + "=" * 70)
print("  Coverage Summary")
print("=" * 70)

if report_txt.exists():
    print(report_txt.read_text(encoding="utf-8"))

print(f"\n  XML  : {report_xml}")
print(f"  HTML : {report_html}")
print(f"  TXT  : {report_txt}")
print("=" * 70)

sys.exit(result.returncode)
