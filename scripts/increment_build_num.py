import os

for path, _, files in os.walk('src/kernel'):
     if "version.h" in files:
            with open(os.path.join(path, "version.h"), 'r') as f:
                lines = f.read().split('\n')
            for i, line in enumerate(lines):
                if not line.split(" ")[0] == "#define": continue
                if not len(line.split(" ")) > 1: continue
                if not line.split(" ")[1].upper() == "BUILD_NUMBER": continue
                if not len(line.split(" ")) > 2: exit(1)
                lines[i] = " ".join(line.split(" ")[:-1] + [str(int(line.split(" ")[2]) + 1)])
                break
            with open(os.path.join(path, "version.h"), 'w') as f:
                f.write('\r\n'.join(lines))
            exit()