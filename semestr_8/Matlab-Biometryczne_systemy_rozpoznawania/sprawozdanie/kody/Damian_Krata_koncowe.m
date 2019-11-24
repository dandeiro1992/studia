clear all;
close all;
clc;


%A = imread('D:\Semestr 8\baza_teczowki\CASIA-IrisV3\CASIA-IrisV3-Interval\001\L\S1001L01.jpg');
%imshow(A)
A=imread('C:\Users\Damian\Desktop\S1001L07.jpg');
imshow(A)
%[centers, radii] = imfindcircles(A,[15 30],'ObjectPolarity','dark','Sensitivity',0.92,'EdgeThreshold',0,1);
%centersStrong5 = centers(1:1,:); 
%radiiStrong5 = radii(1:1);
%metricStrong5 = metric(1:1);

%viscircles(centers, radii,'EdgeColor','b');
ile_podzialow=128;
[row1, col1, r1]=findcircle(A,100,250,0.4,15,0.1,0.1,1,0.5)
[row, col, r]=findcircle(A,30,60,0.4,15,0.1,0.10,1,0.5)
srodek=[(col+col1)/2 (row+row1)/2]
% viscircles([col row], r,'EdgeColor','b');
% viscircles([col row], r1-15,'EdgeColor','b');
srednie_r=(r1-15)
viscircles([srodek(1) srodek(2)], r,'EdgeColor','b');
viscircles([srodek(1) srodek(2)], r1-15,'EdgeColor','b');
powierzchnia=pi*(r1-15)^2-pi*r^2
[sizex, sizey, sizez]= size(A);
blank = zeros(sizex,sizey,sizez);
rectangle=zeros(140,140);
sizex
sizey
sizez
T=[];
P = zeros(ile_podzialow, 1);
for i=1:sizex
        for j=1:sizey
            if(((i-srodek(1))^2+(j-srodek(2))^2)<=srednie_r^2)
                T=horzcat(T,A(i,j));
            end
        end
end

image = abs(dct2(T));
wektor_po_zigzagu = zigzag(image)

length = size(wektor_po_zigzagu,2)/ile_podzialow;
        for index=1:ile_podzialow
            tmp = mean(wektor_po_zigzagu(length*(index-1)+1:length*index));
            P(index,1) = tmp;
        end