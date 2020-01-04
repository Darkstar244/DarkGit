close all;
clear all;
clc;
files = dir(fullfile('D:/Matvideo/Doll/','*.jpg'));
for i_1=1:730%帧数
    path_1='D:/Matvideo/Doll/';%视频路径
     disp(i_1); 
     path_1=strcat(path_1,num2str(i_1));
    p_1=strcat(path_1,'.jpg');
   
target=imread(p_1);
lengthFiles = length(files);
error=0;
data=[];%预分配内存
for i = 1:lengthFiles
    try
        Img = imread(strcat('D:/Matvideo/Doll/',files(i).name));%文件所在路径
        %改变大小
        newimg=imresize(Img,[10,10]);
        %获取三分量
        imager=newimg(:,:,1);
        imageg=newimg(:,:,2);
        imageb=newimg(:,:,3);
        %统计平均值
        image_r=0;
        image_g=0;
        image_b=0;
        for m=1:10
            for j=1:10
                image_r=int32(image_r)+int32(imager(m,j));
                image_g=int32(image_g)+int32(imager(m,j));
                image_b=int32(image_b)+int32(imager(m,j));
                %fprintf('i is  %d image_r is %d  image_g is  %d  image_b is %d\n',i,image_r,image_g,image_b)
            end
        end
        fprintf('i is  %d image_r is %d  image_g is  %d  image_b is %d\n',i,image_r,image_g,image_b)
        image_r=image_r/100;
        image_g=image_g/100;
        image_b=image_b/100;
        data=[data image_r image_g image_b];
        %disp(strcat('D:\document\GitHub\homework\digital image processing\image_spider\animation\',files(i).name)) %打印文件路径
        %imshow(Img)
    catch
        disp(strcat('D:/Matvideo/Doll/',files(i).name)) %打印文件路径
        error=error+1;
    end
end
sizetarget=size(target);
x=sizetarget(1,1);
y=sizetarget(1,2);
t_image_r=0;
t_image_g=0;
t_image_b=0;
for i=1:10:x
    for j=1:10:y
        if (i+9>x||j+9>y)
            continue;
        end
        for m=i:i+9
            for n=j:j+9
                t_image_r=int32(t_image_r)+int32(target(m,n,1));
                t_image_g=int32(t_image_g)+int32(target(m,n,2));
                t_image_b=int32(t_image_b)+int32(target(m,n,3));
            end
        end
        t_image_r=t_image_r/100;
        t_image_g=t_image_g/100;
        t_image_b=t_image_b/100;
        %fprintf('r is %d  g is  %d  b is  %d\n',t_image_r,t_image_g,t_image_b)
        cha=765;
        mini=1;
        sizedata=size(data);
        for q=1:3:sizedata(1,2)
            cha1=abs(t_image_r-data(q))+abs(t_image_g-data(q+1))+abs(t_image_b-data(q+2));
            if(cha1<cha)
                cha=cha1;
                mini=floor(q/3)+1;
            end
        end
        %disp(mini)
        Img = imread(strcat('D:/Matvideo/Doll/',files(mini).name));%文件所在路径
        newimg=imresize(Img,[10,10]);
        for q=0:9
            for p=0:9
                target(i+q,j+p,1)=newimg(q+1,p+1,1);
                target(i+q,j+p,2)=newimg(q+1,p+1,2);
                target(i+q,j+p,3)=newimg(q+1,p+1,3);
            end
        end
        fprintf('x is %d  y is  %d\n',i,j)
    end
end
lujing=strcat('D:/Matvideo/Complete/',num2str(i_1));%输出路径
    lujing=strcat(lujing,'.jpg');
imwrite(target,lujing);
end