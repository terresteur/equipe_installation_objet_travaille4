import os
import re

# Path to your help patches folder
FOLDER = "."   # current folder, change if needed
OUTPUT = "Index.md"

lines = ["## Abstractions\n"]

for filename in sorted(os.listdir(FOLDER)):
    if filename.endswith("-help.pd"):
        object_name = filename[:-8]  # remove "-help.pd"
        description = ""

        with open(os.path.join(FOLDER, filename), "r", encoding="utf-8") as f:
            for line in f:
               # look for "Description:" or "Description :"
                match = re.search(r"Description\s*:\s*(.*)", line)
                if match:
                    description = match.group(1).strip()
                    # remove all backslashes
                    description = description.replace(" \\", "")
                    if description.endswith(";"):
                        description = description[:-1].strip()
                    break

        if description:
            lines.append(f"- `{object_name}`: {description}")
        else:
            lines.append(f"- `{object_name}`")

with open(os.path.join(FOLDER, OUTPUT), "w", encoding="utf-8") as f:
    f.write("\n".join(lines))

print(f"✅ {OUTPUT} created with {len(lines)-1} entries.")
