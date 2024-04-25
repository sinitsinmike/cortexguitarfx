import numpy as np
import matplotlib.pyplot as plt

def remez_row(x_val,i,order):
    result = np.zeros(order)
    cnt=0
    for c in range(order-1):
        result[c] = x_val**c

    result[order-1] = (-1)**i
    return result

def find_zero(f_approx,a, b):
    delta_min = 0.0000001
    max_iter = 1000
    p2 = b
    p1 = a
    delta = p2-p1
    is_falling = f_approx(a) > f_approx(b)
    iterations = 0 
    while abs(delta) > delta_min and iterations < max_iter:
        fa = f_approx(p1)
        fb = f_approx(p2)
        if (fa  < 0 and fb < 0 and is_falling) or (fa  > 0 and fb > 0 and not is_falling):
            p2 -= delta
            p1 -= delta
        elif (fa  < 0 and fb < 0 and not is_falling) or (fa  > 0 and fb > 0 and is_falling):
            p2 += delta
            p1 += delta
        else:
            p2 -= delta/2
        delta = p2 - p1
        iterations += 1
    return (p1+p2)/2

def find_extrema(f_approx,a,b):
    p_left = a
    p_right = a + (b-a)*0.5
    if (f_approx(p_right) < 0):
        coeff = -1
    else:
        coeff = 1
    

if __name__ == "__main__":
    order = 8
    scaling = 20.0
    x_points = np.linspace(1.0,2.0,order)

    y_points = np.log10(x_points)
    remez_matrix = np.zeros((order,order))
    dx = 0.0000001
    tol = 0.0001
    cont = True

    xplot = np.linspace(1.0,2.0,256)
    while cont:
        for c in range(order):
            remez_matrix[c]= remez_row(x_points[c],c,order)
        y_points = np.log10(x_points)
        coeffs_and_e = np.linalg.solve(remez_matrix,y_points)
        coeffs = coeffs_and_e[:-1]
        residual = lambda x: np.log10(x)  - np.polyval(np.flip(coeffs),x)
        zeroes = []
        for c in range(order-1):
            zeroes.append(find_zero(residual,x_points[c],x_points[c+1]))
        diff_poly = lambda x: (residual(x + dx) - residual(x-dx))/(2*dx)
        extremas = []
        for c in range(order-2):
            extremas.append(find_zero(diff_poly,zeroes[c], zeroes[c+1]))
        x_points[1:-1] = extremas
        #plt.plot(xplot,residual(xplot))
        #plt.plot(zeroes,np.zeros(order-1),'+k')
        #plt.plot(extremas,residual(extremas),'+r')
        #plt.show()
        errors = np.array([abs(residual(x)) for x in x_points])
        avg_error = np.mean(errors)
        cont = np.max(np.abs(errors - avg_error)) > tol*avg_error
    
    yplot_exact = np.log10(xplot)
    yplot_approx = np.polyval(np.flip(coeffs),xplot)
    print("coefficients: ")
    print(coeffs*scaling)
    print("error: ")
    print(coeffs_and_e[-1])
    plt.plot(xplot,yplot_exact,'-g')
    plt.plot(xplot,yplot_approx,'.r')
    plt.show()

