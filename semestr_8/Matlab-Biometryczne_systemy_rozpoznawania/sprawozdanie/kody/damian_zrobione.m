clear all;
close all;
clc;

absolutePath = 'D:\Semestr 8\Wat - 8 semestr\biometryczne systemy rozpoznawania\koncowe\baza_teczowki\';
nazwy_ludzi = ['001';'002';'007';'008';'011';'019';'028';'029';'030';'036';];
ilosc_ludzi = 10;
nazwy_probek = ['1';'2';'3';'4';'5';'6';'7';'8'];
ilosc_probek =8;

ile_podzialow = 128;

m=4;

P = zeros(ile_podzialow, ilosc_ludzi*m);

T = [];

I = eye(ilosc_ludzi);
for i=1:m
    T = [T I];
end

for i = 1:m
    for j = 1:ilosc_ludzi
        path = strcat(absolutePath, nazwy_ludzi(j,:),'\L\S1',nazwy_ludzi(j,:),'L0', nazwy_probek(i,:),'.jpg');
        A=imread(path);
        [row1, col1, r1]=findcircle(A,100,250,0.4,15,0.1,0.1,1,0.5);
        [row, col, r]=findcircle(A,30,60,0.4,15,0.1,0.10,1,0.5);
        srodek=[(col+col1)/2 (row+row1)/2];
        srednie_r=(r1-15);
        [sizex, sizey, sizez]= size(A);
        blank = zeros(sizex,sizey,sizez);
        K=[];
        for n=1:sizex
            for l=1:sizey
                if(((n-srodek(1))^2+(l-srodek(2))^2)<=srednie_r^2)
                    if(((n-srodek(1))^2+(l-srodek(2))^2)>r^2)
                        K=horzcat(K,A(n,l));
                    end
                end
            end
        end
        
        image = abs(dct2(K));
        wektor_po_zigzagu = zigzag(image);
        
        length = size(wektor_po_zigzagu,2)/ile_podzialow;
        for index=1:ile_podzialow
            tmp = mean(wektor_po_zigzagu(length*(index-1)+1:length*index));
            P(index,ilosc_ludzi*(i-1)+j) = tmp;
        end
    end
end
% utworzenie modelu sieci nieliniowej wielowarstwowej
[w,k]=size(P);
R=zeros(w,2);
R(:,1)=min(P');
R(:,2)=max(P');
net = newff(R,[ile_podzialow round((ile_podzialow+ilosc_ludzi)/2) ilosc_ludzi],{'logsig' 'logsig' 'logsig'},'traingdx');

%ustawienie parametrów treningu 
net.trainParam.epochs = 20000;
net.trainParam.goal=0.000000001;
net.trainParam.min_grad=0.000000001;

%trening, uczenie
net = train(net,P,T);
%dzia³anie sieci (symulacja)
Y = sim(net,P);
Y = round(Y)
P
wsp = 0;
index = 1;
for col = Y
    if(col == T(:,index))
        wsp = wsp + 1;
    end
    index = index + 1;
end
wsp = wsp / (ilosc_ludzi*m)
PP = zeros(ile_podzialow, ilosc_ludzi*m);
for i = m+1:ilosc_probek
    for j = 1:ilosc_ludzi
         path = strcat(absolutePath, nazwy_ludzi(j,:),'\L\S1',nazwy_ludzi(j,:),'L0', nazwy_probek(i,:),'.jpg');
        A=imread(path);
        [row1, col1, r1]=findcircle(A,100,250,0.4,15,0.1,0.1,1,0.5);
        [row, col, r]=findcircle(A,30,60,0.4,15,0.1,0.10,1,0.5);
        srodek=[(col+col1)/2 (row+row1)/2];
        srednie_r=(r1-15);
        [sizex, sizey, sizez]= size(A);
        blank = zeros(sizex,sizey,sizez);
        K=[];
        for n=1:sizex
            for l=1:sizey
                if(((n-srodek(1))^2+(l-srodek(2))^2)<=srednie_r^2)
                    if(((n-srodek(1))^2+(l-srodek(2))^2)>r^2)
                        K=horzcat(K,A(n,l));
                    end
                end
            end
        end
        
        image = abs(dct2(K));
        wektor_po_zigzagu = zigzag(image);
        
        length = size(wektor_po_zigzagu,2)/ile_podzialow;
        for index=1:ile_podzialow
            tmp = mean(wektor_po_zigzagu(length*(index-1)+1:length*index));
            PP(index,ilosc_ludzi*(i-m)+j-ilosc_ludzi) = tmp;
        end
    end
end
PP
Y = sim(net,PP);
Y = round(Y)
    
wsp1 = 0;
index = 1;
for col = Y
    if(col == T(:,index))
        wsp1 = wsp1 + 1;
    end
    index = index + 1;
end

wsp1 = wsp1 / (ilosc_ludzi*m)