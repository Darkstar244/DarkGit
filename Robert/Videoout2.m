clear;
clc;
 
WriterObj=VideoWriter('cxk.avi', 'Uncompressed AVI');%·��+����ļ���+��ʽ
open(WriterObj);
for i=1:1477
  pic='D:/Matvideo/robert/';%���֡ͼ��·��
  pic=strcat(pic,num2str(i));
  ppic=strcat(pic,'.jpg');
  frame=imread(ppic);% ��ȡͼ�񣬷��ڱ���frame��
  disp(ppic);
  writeVideo(WriterObj,frame);% ��frame�ŵ�����WriterObj��
end
close(WriterObj);
