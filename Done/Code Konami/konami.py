


file = open('/home/alex/Desktop/Projects/PYDefis/Work in progress/Currently trying/Code Konami/in.txt')
amountOfCode = file.readline()
amountOfCode = int(amountOfCode)
map = {}

for i in range(amountOfCode):
    line = file.readline()
    code = line[0] + line[1]
    value = line[6]
    map[code] = value
secret = file.readline()
message = '' 
while(secret != ''):
    for i in range(0,len(secret)-1,2):
        code = secret[i] + secret[i+1]
        message += map[code]
    secret = file.readline()
print(message)