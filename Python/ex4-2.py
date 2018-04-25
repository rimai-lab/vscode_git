def g(w):
    return 2 * w - 6
    # f'(w) = (w^2 - 6w + 9)' = 2w - 6

def numerical_gradient(f, w):
    h = 0.001
    return (f(w + h)- f(w - h)) / (2 * h)

def gradient_descent(df, initial):
    x = initial
    for _ in range(100):
        x -= 0.1 * df(x)
    return x

fx = lambda w: w ** 2 - 6 * w + 9
numgrd = lambda w: numerical_gradient(fx, w)

print("手計算での導関数g(w) = f'(w)")
print(gradient_descent(g, 0))

print("\n数値微分の関数numerical_gradient")
print(gradient_descent(numgrd, 0))