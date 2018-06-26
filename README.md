idsc_shapematching
==================

shape matching algorithm from haibin lin

I solve two problem in this algorithm.

First one is his angle matrix which was calculated in bellman_ford. I think the matrix is wrong because it cannot achieve 
rotated invarience and scaled invarience. When I inverse the matrix, it can! Well it means when you rotate an elephant and 
get elephant2, two contour elephant1 and elephant2 should match near 100%. If I don't inverse the matrix, the match point is 70
or 80 or maybe less. But when I do the inversion, the match point reach 98 99! And I use spfa to optimise bellman_ford.

Second I solve the symmetry problem. It is show in elephant.bmp and elephant34.bmp. 

