clear all;
cd = 'D:/Matvideo/jie/';
waveFiles = dir(fullfile(cd,'*.wav'));%��ȡ���е�WAV
len = size(waveFiles,1);%�ܳ���

%Z = [];%��ʼ��Z
Z(2821021,2)=0;%Ԥ�����ڴ棨���������Ļ�����ô����ǳ�����
for i =1:792%����֡������
   fileName=strcat('D:/Matvideo/jie/',num2str(i));
   fileName=strcat(fileName,'.wav');
    disp(fileName);
    [X, fs] = audioread(fileName);
X=X( ( 1 : int32(fs*0.52) ), : );%��ȡÿ����Ƶ��ǰ0.52s(��Ȼ�������ܴ�)
    
    Z = [Z; X];
    end
%for i = 1:792
   % fileName=strcat('D:/Matvideo/jie/',num2str(792-i+1));
   %fileName=strcat(fileName,'.wav');
   % disp(fileName);
   % [X, fs] = audioread(fileName);
   
 
   % Z = [Z; X];
%end
lujing=strcat('D:/Matvideo/','zed.wav');%���·��
audiowrite(lujing,Z,2*fs);%���