# Function to check if a number is a palindrome
def is_palindrome(n):
    return str(n) == str(n)[::-1]

# Initialize variables to keep track of the largest palindrome and its factors
largest_palindrome = 0
factor1 = 0
factor2 = 0

# Loop through all possible 3-digit numbers for both factors
for i in range(100, 1000):
    for j in range(i, 1000):  # Start from i to avoid duplicate products
        product = i * j  # Calculate the product

        # Check if the product is a palindrome and greater than the current largest
        if is_palindrome(product) and product > largest_palindrome:
            largest_palindrome = product
            factor1 = i
            factor2 = j

# Print the largest palindrome and its factors
print(f"The largest palindrome made from the product of two 3-digit numbers is {largest_palindrome} = {factor1} x {factor2}")

# Save the result in the 102-result file without newline or extra space
with open("102-result", "w") as result_file:
    result_file.write(str(largest_palindrome))
