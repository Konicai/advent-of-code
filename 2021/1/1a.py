
count = 0
with open("measurements.txt", "r") as file:
    
    last = None # The previous depth measurement
    
    for line in file:
        
        line = line.strip() # Remove whitespace, etc
        depth = int(line) # Kinda risky as long as the file is okay
        
        if last != None and depth > last:
            count += 1
            
        last = depth # Save the current depth for the next iteration

print(count)            
            
            
         
