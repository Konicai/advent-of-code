
lines = []
with open('input.txt', 'r') as data:
	for line in data:
		lines.append(line.strip())

# Amount of bits per word
bit_length = len(lines[0])
# Amount of words
word_amount = len(lines)

# Indices of words that may be the solution
possible_o = [*range(word_amount)]
possible_c = [*range(word_amount)]

oxygen_rating = None
carbon_rating = None


for i in range(bit_length):

	count_0 = 0
	count_1 = 0
	for j in range(word_amount):
		bit = lines[j][i]
		if bit == '0':
			count_0 += 1
		elif bit == '1':
			count_1 += 1
		else:
			raise Exception(f'Got {bit} instead of a bit on row {count_0 + count_1}, column {i}')

	if count_0 == count_1:
		# 1 and 0 bits are equally common
		o_matcher = lambda x: x == 0
		c_matcher = lambda x: x == 1
		#print("\tNeither more common")
	elif count_0 > count_1:
		# 0 bits are most common
		o_matcher = lambda x: x == 0
		c_matcher = lambda x: x == 1
		#print("\t0 more common")
	elif count_1 > count_0:
		# 1 bits are most common
		o_matcher = lambda x: x == 1
		c_matcher = lambda x: x == 0
		#print("\t1 more common")
	else:
		raise Exception

	print()
	print(possible_o)
	print(possible_c)

	print("OXYGEN")
	if oxygen_rating == None:
		for j in list(possible_o):
			word = lines[j]
			print("word:", word)
			bit = int(word[i])
			print("bit", bit)
			if not o_matcher(bit):
				print("marked for removal")
				possible_o.remove(j)

	print("CARBON")




	if carbon_rating == None:
		for j in list(possible_c):
			word = lines[j]
			#print("word", word)
			bit = int(word[i])
			#print("bit:", bit)
			if not c_matcher(bit):
				#print("marked for removal")
				possible_c.remove(j)

	if len(possible_o) == 1:
		oxygen_rating = lines[possible_o[0]]
	if len(possible_c) == 1:
		carbon_rating = lines[possible_c[0]]


print(possible_o)
print(possible_c)

print("Oxygen Rating:", int(oxygen_rating, 2))
print(oxygen_rating)
print("Carbon Rating:", int(carbon_rating, 2))
print(carbon_rating)
