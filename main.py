import time as ti
import cv2 as cv
import matplotlib.pyplot as plt


def hash_array(img_array):
    hash = 5
    for num in img_array:
        hash = hash << num
    return hash

def hash_mat(img_array):
    seed = round(ti.time())
    seed = 7
    img_arrayBW = cv.cvtColor(img_array, cv.COLOR_BGR2GRAY)
    rows, cols = img_arrayBW.shape
    for x in range(cols):
        for y in range(rows):
            seed = (seed << img_arrayBW[y][x]%10)%100000
    if round(ti.time())%2:
        seed = seed + 1
    return seed


MAX_NUMS = 100
num_freqs = [0]*MAX_NUMS
i = 0
i_ceil = 256
video_stream = cv.VideoCapture(0)
while video_stream.isOpened():
    ret, frame = video_stream.read()
    current_num = hash_mat(frame)%MAX_NUMS
    print(str(i) + "/" + str(i_ceil) + ": " + str(current_num))
    if i < i_ceil:
        num_freqs[current_num] += 1
        i += 1
    else:
        break

num_names = []
for i in range(MAX_NUMS):
    num_names.append(str(i))

fig = plt.figure()
ax = fig.add_axes([0,0,1,1])
print(num_freqs)
ax.bar(num_names,num_freqs)
plt.show()


