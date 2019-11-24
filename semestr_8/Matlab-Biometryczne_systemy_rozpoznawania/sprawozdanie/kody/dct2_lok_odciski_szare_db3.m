clear all;close all;clc;
% Pozyskanie i wyswietlenie obrazu
[x1,map]=imread('.\DB3_B\103_1','tif');x1=x1(:,:,1);
x1=ceil(x1);
figure(1);subplot(2,3,1);imshow(x1);
%=================================================
% wyznaczenie transformat lokalnych dct 
lwierszy=3;
lkolumn=3;
x1=double(x1)-0.5;
[w,k]=size(x1);
szer_kol=floor(k/lkolumn);
szer_wiersza=floor(w/lwierszy);
Xkol=[];Xwiersz=[];
for i=1:lwierszy
    for j=1:lkolumn
        xlok=x1(szer_wiersza*(i-1)+1:szer_wiersza*i,szer_kol*(j-1)+1:szer_kol*j);
        X=abs(dct2(xlok));X(1,1)=0;
        Xwiersz=[Xwiersz X];
    end;
    Xkol=[Xkol;Xwiersz];
    Xwiersz=[];
end;
X=Xkol;
X=floor((X/max(max(X))).^(1/4)*256);
figure(1);subplot(2,3,4);image(X);          
% Pozyskanie i wyswietlenie obrazu
[x1,map]=imread('.\DB3_B\102_7','tif');x1=x1(:,:,1);
x1=ceil(x1);
figure(1);subplot(2,3,2);imshow(x1);
%=================================================
% wyznaczenie transformat lokalnych dct 
lwierszy=3;
lkolumn=3;
x1=double(x1)-0.5;
[w,k]=size(x1);
szer_kol=floor(k/lkolumn);
szer_wiersza=floor(w/lwierszy);
Xkol=[];Xwiersz=[];
for i=1:lwierszy
    for j=1:lkolumn
        xlok=x1(szer_wiersza*(i-1)+1:szer_wiersza*i,szer_kol*(j-1)+1:szer_kol*j);
        X=abs(dct2(xlok));X(1,1)=0;
        Xwiersz=[Xwiersz X];
    end;
    Xkol=[Xkol;Xwiersz];
    Xwiersz=[];
end;
X=Xkol;
X=floor((X/max(max(X))).^(1/4)*256);
figure(1);subplot(2,3,5);image(X);
% Pozyskanie i wyswietlenie obrazu
[x1,map]=imread('.\DB3_B\104_5','tif');x1=x1(:,:,1);
x1=ceil(x1);
figure(1);subplot(2,3,3);imshow(x1);
%=================================================
% wyznaczenie transformat lokalnych dct 
lwierszy=3;
lkolumn=3;
x1=double(x1)-0.5;
[w,k]=size(x1);
szer_kol=floor(k/lkolumn);
szer_wiersza=floor(w/lwierszy);
Xkol=[];Xwiersz=[];
for i=1:lwierszy
    for j=1:lkolumn
        xlok=x1(szer_wiersza*(i-1)+1:szer_wiersza*i,szer_kol*(j-1)+1:szer_kol*j);
        X=abs(dct2(xlok));X(1,1)=0;
        Xwiersz=[Xwiersz X];
    end;
    Xkol=[Xkol;Xwiersz];
    Xwiersz=[];
end;
X=Xkol;

X=floor((X/max(max(X))).^(1/4)*256);
figure(1);subplot(2,3,6);image(X);
