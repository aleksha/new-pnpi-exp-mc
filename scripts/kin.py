import matplotlib.pyplot as plt
from math import sqrt, pow, acos, pi

Tp = 992       # MeV
m  = 938.272   # MeV
mu = 3727.379  # MeV

m2=m*m
mu2=mu*mu

E_beam = m + Tp
p_beam = sqrt(pow(E_beam,2)-pow(m,2))

s = pow(E_beam + mu,2)-pow(p_beam,2)

def lam(x,y,z):
    return x*x+y*y+z*z-2.*x*y-2.*x*z-2.*y*z

def s_lam(x,y,z):
    return sqrt(lam(x,y,z))

T_R   = ( lam(s,m2,mu2)/s )/(2*mu)
t_min = - lam(s,m2,mu2)/s

print("Proton beam energy : " + str(Tp) + " MeV")
print("Max. recoil energy : " + str(T_R) + " MeV")

T_lst = []
t_lst = []
u_lst = []
x = []
y = []
for i in range(1,200):
    T = 0.1*i
    t = - 2*mu*T
    u = 2.*(m2+mu2) - s - t
    theta_1 = acos( ( (s-m2-mu2)*(m2+mu2-u)+2.*mu2*(t-2.*m2) ) / ( s_lam(s,m2,mu2)*s_lam(u,mu2,m2) ) )
    theta_2 = acos( ( (s-m2-mu2)*(2.*mu2-t)+2.*mu2*(u-m2-mu2) ) / ( s_lam(s,m2,mu2)*s_lam(t,mu2,mu2)) )
    x.append( T )
    y.append( theta_2*180./pi )


plt.plot(x,y,"r-")
plt.show()
