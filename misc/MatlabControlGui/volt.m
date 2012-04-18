r1 = 10000;
r2 = 100:100:50000;

I = 1.25 / r1;

Vout = 1.25 * (1 + r2./r1) + I.*r2

plot(r2, Vout)
title('R2 vs voltage at a constant r1 of 10000');


%r2 =22000;