function [ im2 ] = symmetry2( im )
[n,m]=size(im);
im2=zeros(n,m);

for i=1:n
    for j=1:m
        im2(i,j)=im(i,m-j+1);
    end
end
imshow(im2);
end

