%Jonathan Benusa
function [decNum] = BinaryToDecimal(str,twos)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    L = length(str);
    decNum = 0;
    temp = L;
    if twos==2        %if the function is in twos complement
        index = 2;
        if str(1)=='1'        %if the number is negative store decNum as the smallest number possible for the number of bits
            decNum = -2^(L-1);
        end
        while index<=L
            if str(index)=='1'
                decNum = decNum +2^(temp-index);      %for example 01000 would have 2^(3)
            end
            index = index +1;
        end
    else               %if the number isn't in twos complement
        index = 1;
        while index<=L
            if str(index)=='1'
                decNum = decNum +2^(temp-index);      %for example 10000 would have 2^(4)
            end
            index = index +1;
    end
end

