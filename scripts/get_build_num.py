import os

for path, _, files in os.walk('src/kernel'):
     if "version.h" in files:
            with open(os.path.join(path, "version.h"), 'r') as f:
                lines = f.read().split('\n')
            for line in lines:
                if not line.split(" ")[0] == "#define": continue
                if not len(line.split(" ")) > 1: continue
                if not line.split(" ")[1].upper() == "BUILD_NUMBER": continue
                if not len(line.split(" ")) > 2: exit(1)
                print(line.split(" ")[2])
                exit()