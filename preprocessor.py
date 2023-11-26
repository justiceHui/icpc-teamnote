# Note: make build/tempfile.tmp before compile
# $pdflatex = 'pdflatex --shell-escape'

import sys

def remove_header(filename):
    f = open(filename, 'r')
    lines = f.readlines()
    f.close()
    st = 0
    while st < len(lines) and len(lines[st].strip()) == 0: st += 1
    if lines[st] == '/**\n':
        while st < len(lines) and '*/' not in lines[st]: st += 1
        st += 1
        while st < len(lines) and len(lines[st].strip()) == 0: st += 1
    return ''.join(lines[st:])

if __name__ == '__main__':
    input_file = sys.argv[1]
    output_file = sys.argv[2]
    content = remove_header(input_file)
    f = open(output_file, 'w')
    f.write(content)
    f.close()