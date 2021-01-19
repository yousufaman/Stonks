import matplotlib.pyplot as plt 
import csv
from random import randint
import statistics
from math import sqrt
from sklearn.metrics import mean_squared_error




#for price history
x = []
y = [100,99.80311647,99.72990912,99.65636726,99.6556732,99.69786154,99.74150906,99.73389665,99.79820824,99.79761168,99.79823002,99.79823002,99.78262647,99.78262647,99.78262647,99.73969133,99.73773184,99.73797132,99.73490099,99.73490099,99.73490099,99.734149,99.734149,99.77562657,99.7592583,99.75836796,99.71464245,99.71464245,99.71562527,99.64409042,99.62799208,99.62799208,99.62799208,99.62799208,99.57002365,99.66995111,99.66896711,99.68228756,99.68365737,99.66949599,99.56961951,99.56893026,99.56844997,99.56717845,99.56717845,99.63750043,99.56438822,99.49161966,99.29320141,99.27805847,99.29122139,99.29122139,99.29122139,99.29057403,99.36138729,99.36223967,99.36223967,99.31930126,99.20495047,99.13329905,99.13339801,98.77920303,98.82217857,98.82098415,98.80793197,98.80830788,98.84958174,98.84852822,98.84852822,98.57965834,98.28474207,98.29742855,98.29860256,98.29842983,98.28496445,97.93797363,97.92403829,97.93724476,97.93919152,97.92627805,97.97024764,97.96947664,97.97006179,97.99765621,97.98403421,97.97144908,97.97192716,97.97139071,97.80561647,97.59646317,97.736,97.8226,97.8727,97.872,97.8722,97.8693,97.8675,97.8656,97.8617,97.8596,97.8676,97.8772,97.8849,97.8893,97.8925,97.8952,97.8981,97.9011,97.9043,97.9078,97.9115,97.9153,97.919,97.9225,97.9257,97.9289,97.9321,97.9352,97.9384,97.9415,97.9446,97.9477,97.9507,97.9537,97.9566,97.9595,97.9623,97.9652,97.968,97.9707,97.9735,97.9762,97.9788,97.9815,97.984,97.9866,97.9891,97.9916,97.9941,97.9965,97.9989,98.0013,98.0036,98.0059,98.0082,98.0105,98.0127,98.0149,98.0171,98.0192,98.0214,98.0234,98.0255,98.0275,98.0295,98.0316,98.0335,98.0354,98.0374,98.0393,98.0411,98.043,98.0448,98.0466,98.0484,98.0501,98.0519,98.0536,98.0553,98.0569,98.0586,98.0602,98.0618,98.0634,98.0649,98.0665,98.0681,98.0696,98.0711,98.0726]
for i in range(180):
    x.append(i)

#with open('opt.csv', mode ='r') as output:
#    reader = csv.reader(output , delimiter=";" )
#    for row in reader:
#        x.append(row)
max_y = max(y)
pos_x = y.index(max_y)
max_x = x[pos_x]
#print(max_y)
#print("Standard deviation for main data is %s" %(statistics.stdev(y)))

#for output price
a = []
b = [100,100.001,99.9982,100.006,100,99.9862,99.9596,99.9229,99.8817,99.8437,99.8059,99.7699,99.7366,99.7032,99.6684,99.632,99.6016,99.6157,99.6187,99.6375,99.6488,99.6556,99.6553,99.6581,99.6635,99.6666,99.6715,99.6739,99.6762,99.6785,99.6816,99.684,99.6878,99.6924,99.6983,99.7007,99.7064,99.7148,99.7181,99.7262,99.7325,99.7374,99.7426,99.7468,99.75,99.754,99.7579,99.7612,99.7639,99.7681,99.7721,99.7757,99.7793,99.7831,99.7906,99.7951,99.8007,99.8076,99.8133,99.8184,99.8239,99.8294,99.8326,99.8365,99.8408,99.8443,99.85,99.8538,99.8561,99.8599,99.8653,99.8713,99.8748,99.88,99.886,99.8916,99.8968,99.9033,99.9084,99.9131,99.916,99.9211,99.9258,99.9297,99.9333,99.9357,99.9378,99.9415,99.9462,99.9512,99.9569,99.9628,99.9683,99.9738,99.9795,99.9851,99.9907,99.9946,99.9971,100.001,100.006,100.009,100.011,100.014,100.018,100.023,100.027,100.031,100.036,100.041,100.046,100.051,100.054,100.058,100.061,100.063,100.066,100.069,100.072,100.076,100.08,100.082,100.085,100.09,100.092,100.097,100.101,100.104,100.107,100.11,100.113,100.117,100.121,100.126,100.129,100.133,100.135,100.137,100.14,100.144,100.146,100.149,100.153,100.157,100.16,100.164,100.168,100.172,100.175,100.175,100.178,100.181,100.184,100.186,100.188,100.19,100.194,100.197,100.199,100.202,100.205,100.206,100.209,100.211,100.215,100.216,100.218,100.22,100.222,100.224,100.226,100.228,100.231,100.232,100.233,100.236,100.238,100.239,100.24,100.242]
for i in range(180):
    a.append(i)

max_b = max(b)
pos_a = b.index(max_b)
max_a = a[pos_a]

min_b = min(b)
mpos_a = b.index(min_b)
min_a = a[mpos_a]
#print("Standard deviation for optimal results is %s" %(statistics.stdev(b)))

rms = mean_squared_error(y,b, squared=False)


plt.plot(x,y, 'r')
plt.plot(a,b, 'g')
plt.legend(["Price History", "Prediction"])

print("\n****STATISTICS FOR OBTAINED BLACK SCHOLES PREDICTION****\n\n")
print("Highest Prediction : $", max_b, "At " , max_a, " minutes")
print("Lowest Prediction : $", min_b, "At " , min_a, " minutes")
print("The Root Mean Error: ", round(sqrt(rms), 2))
print("Accuracy of Prediction : ", round(100-rms, 2), "%")


plt.show()