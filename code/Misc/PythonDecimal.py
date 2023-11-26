from fractions import Fraction
from decimal import Decimal, getcontext
getcontext().prec = 250 # set precision
N, two, itwo = 200, Decimal(2), Decimal(0.5)
# sin(x) = sum (-1)^n x^(2n+1) / (2n+1)!
# cos(x) = sum (-1)^n x^(2n) / (2n)!
def angle(cosT):
  #given cos(theta) in decimal return theta
  for i in range(N): cosT=((cosT+1)/two)**itwo
  sinT = (1-cosT*cosT)**itwo
  return sinT*(2**N)
pi = angle(Decimal(-1))