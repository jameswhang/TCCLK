import re
f = open('otccelf.c', 'r')
t = open('otccelf_translated.c', 'w')

defines = {}
for line in f:
  if "#define" in line:
    words = line.split(' ') 
    print words[0]
    print words[1]
    print words[2]
    defines[words[1]] = words[2]
  else:
    words = line.replace('(', ' ').replace(')', ' ').replace('{', ' ').replace('}', ' ').split(' ') 
    for word in words:
      if word in defines:
        t.write(defines[word])
      else:
        t.write(word)
      t.write(' ')

