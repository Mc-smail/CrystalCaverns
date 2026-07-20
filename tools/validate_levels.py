#!/usr/bin/env python3
"""Validate Crystal Caverns text level files."""
from pathlib import Path
import sys

ALLOWED = set("#.PCOXE")
REQUIRED_EXACTLY_ONE = {"P": "player start", "E": "exit"}
REQUIRED_AT_LEAST_ONE = {"C": "crystal"}


def validate(path: Path) -> list[str]:
    errors: list[str] = []
    rows = path.read_text(encoding="utf-8").splitlines()

    if not rows:
        return [f"{path}: level is empty"]

    width = len(rows[0])
    if width == 0:
        errors.append(f"{path}: first row is empty")

    counts = {char: 0 for char in ALLOWED}
    for y, row in enumerate(rows, start=1):
        if len(row) != width:
            errors.append(f"{path}: row {y} has width {len(row)}, expected {width}")
        for x, char in enumerate(row, start=1):
            if char not in ALLOWED:
                errors.append(f"{path}: invalid char {char!r} at {x}:{y}")
            else:
                counts[char] += 1

    for char, label in REQUIRED_EXACTLY_ONE.items():
        if counts[char] != 1:
            errors.append(f"{path}: expected exactly one {label} ({char}), found {counts[char]}")

    for char, label in REQUIRED_AT_LEAST_ONE.items():
        if counts[char] < 1:
            errors.append(f"{path}: expected at least one {label} ({char})")

    return errors


def main() -> int:
    level_paths = sorted(Path("assets/levels").glob("*.txt"))
    if not level_paths:
        print("No level files found in assets/levels", file=sys.stderr)
        return 1

    all_errors: list[str] = []
    for path in level_paths:
        all_errors.extend(validate(path))

    if all_errors:
        print("Level validation failed:", file=sys.stderr)
        for error in all_errors:
            print(f"- {error}", file=sys.stderr)
        return 1

    print(f"Validated {len(level_paths)} level file(s).")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
