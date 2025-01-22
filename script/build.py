import argparse
import os
import sys

parser = argparse.ArgumentParser(prog="Build app", description="Build application")

parser.add_argument('preset_name')

args = parser.parse_args()

print(args.preset_name)

file_path = os.path.realpath(__file__)
script_dir = os.path.dirname(file_path)
os.chdir(os.path.dirname(script_dir))

if os.system(f'cmake --preset {args.preset_name}'):
    sys.exit(1)

if os.system(f'cmake --build --preset {args.preset_name}'):
    sys.exit(1)

if os.system(f'cmake --install ./build/{args.preset_name} --config {args.preset_name.title()}'):
    sys.exit(1)