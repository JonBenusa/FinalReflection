%Jonathan Benusa
function [BinaryNum] = DecimalToBinary(number,BinaryDigits)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
index = BinaryDigits;
while index>0           %fills an array with zeros the size of BinaryDigits
    BinaryStr(index)=0;
    index = index -1;
end
index = BinaryDigits;
x = number;

while index>1 && number~=0 %only coninue while the array has space and the number is a positive integer
    if mod(number,2)~=0        %if the number is odd for that bit then it gets a one
        BinaryStr(index) = 1;
    end
    number = number / 2 - mod(number,2)/2;       %always divide by 2 to continue and move on to the next bit
    index = index - 1;
end

if x<1
    BinaryStr(1)=1;
end
 
 index = BinaryDigits;

 while BinaryDigits>0
     BinaryNum(BinaryDigits) = '0';
     BinaryDigits = BinaryDigits - 1;
 end
 
 while index>0
    if BinaryStr(index)==1
        BinaryNum(index) = '1';
    end
     index = index -1;
 end
 
  if number>0 
     disp('The number is too large for the number of bits');
     BinaryNum = [];
 end
     
end

