def inverse(u, v):
    """The inverse of :data:`u` *mod* :data:`v`."""

    if v == 0:
        raise ZeroDivisionError("Modulus cannot be zero")
    if v < 0:
        raise ValueError("Modulus cannot be negative")

    u3, v3 = u, v
    u1, v1 = 1, 0
    while v3 > 0:
        q = u3 // v3
        
        u1, v1 = v1, u1 - v1*q
        u3, v3 = v3, u3 - v3*q
        print(q,u3,v3,u1,v1)
    if u3 != 1:
        raise ValueError("No inverse value can be computed")
    while u1<0:
        u1 = u1 + v
    return u1
inverse(3,11)