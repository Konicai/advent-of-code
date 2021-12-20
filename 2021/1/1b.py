
data = []
length = 0
with open("measurements.txt", "r") as file:
    
    one = two = three = None
    
    for line in file:
        
        line = line.strip() # Remove whitespace, etc
        data.append(int(line)) # Risky - as long as the file is okay
        length += 1
           
count = 0 # Amount of trio sums that are larger than the previous

for i in range(0, length - 3, 1):
    this = data[i] + data[i + 1] + data[i + 2]
    following = data[i + 1] + data [i + 2] + data [i + 3]
    
    if following > this:
        count += 1
    
print(count)