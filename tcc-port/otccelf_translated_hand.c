#include<stdio.h>

int e, C, J, m, T, U, K, v, P, i, ak, Q, D, V, al, Z, G, R, y;

L(a) {
 *(char*) D++ = a;
}

w () {
  if(V) {
    m = *(char*)V++;
    if(m == 2) {
      V = 0;
      m = al;
    }
  }
  else
    m = fgetc(ak);
}

am () {
  return isalnum(m) | m == 95;
}

an () {
  if(m == 92) {
    w();
    if(m == 110)
      m = 10;
  }
}

av() {
  int a, s, h;
  while(isspace(m) | m == 35) {
    if(m == 35) {
      w();
      av();
      if(e == 536) {
        av();
        L(32);
        *(int*) e = 1;
        *(int*) (e+4) = D;
      }
      while(m != 10) {
        L(m);
        w();
      }
      L(m);
      L(2);
    }
    w();
  }
  J = 0;
  e = m;
  if(am()) {
    L(32);
    Z = D;
    while(am()) {
      L(m);
      w();
    }
    if(isdigit(e)) {
      C = strtol(Z, 0, 0);
      e = 2;
    }
    else {
      *(char*)D = 32;
      e = strstr(Q, z-1)-Q;
      *(char*)D = 0;
      e = e * 8 + 256;
      if(e > 536) {
        e = T + e;
        if(*(int*)e == 1) {
          V = *(int*)(e+4);
          al = m;
          w();
          av();
        }
      }
    }
  }
  else {
    w();
    if(e == 39) {
      e = 2;
      an();
      C = m;
      w();
      w();
    }
    else if(e == 47 & m == 42) {
      w();
      while(m) {
        while(m != 42)
          w();
        w();
        if(m == 47) m = 0;
      }
      w();
      av();
    }
    else {
      a = "++#m--%am*@R<^1c/@%[_[H3c%@%[_[H3c+@.B#d-@%:_^BKd<<Z/03e>>`/03e<=0f>=/f<@.f>@1f==&g!='g&&k||#l&@.BCh^@.BSi|@.B+j~@/%Yd!@&d*@b";
      while(s = *(char*)a++) {
        h = *(char*) a++;
        C = 0;
        while((J = *(char*)a++ - 98) < 0)
          C = C * 64 + J + 64;
        if(s == e & (h == m | h == 64)) {
          if(h == m) {
            w();
            e = 1;
          }
          break;
        }
      }
    }
  }
}
aw(d) {
  while(d && d!= -1) {
    *(int*)v++ = d;
    d = d >> 8;
  }
}
E(a, d) {
  *(char*) a++ = d;
  *(char*) a++ = d >> 8;
  *(char*) a++ = d >> 16;
  *(char*) a++ = d >> 24;
}
ao(a) {
  int d;
  while(a) {
    d = ao(a);
    if( *(int*)(a-1) == 5) {
      if(z >= G && z < i)
        E(a, z+y);
      else
        E(a, z-K+R+y);
    }
    else {
      E(a, z-a-4);
    }
    a = d; 
  }
}

H(a) {
  ap(a, v);
}

x(d, a) {
  aw(d);
  E(v, a);
  a = v;
  v = v + 4;
  return a;
}

M(a) {
  x(184, a);
}

I(a) {
  return x(233, a);
}

aa(s, a) {
  aw(1032325);
  return x(132+s, a);
}

aq(a) {
  return aw(49465);
  M(0);


