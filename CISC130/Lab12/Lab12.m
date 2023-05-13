%Jonathan Benusa
clear
clc
prompt = 'What would you like to find? Type exit to quit. ';
a = input(prompt,'s');



while 1 ~= strcmp(a,'exit') %checks to see if exit was typed
    L = 0;
    L = strlength(a);
    height = 0;
    radius = 0;
    a(L+1) = ' ';
    
    if 1==contains(a,'cylinder') && 1==count(a,'radius of') && 1==count(a,'height of') %if the string has the word cylinder and has the reqired                                                                                                                        %information
        heightLoc = strfind(a,'height')+10;
        while a(heightLoc)~=' ' && heightLoc~=L+1        %finds where the hieght is in number form in the string and stores it
            height = height * 10;           %next digit
            height = height +str2num(a(heightLoc));     %this turns the char to a number
            heightLoc = heightLoc +1;
        end
        radiusLoc = strfind(a,'radius of')+10;
        while a(radiusLoc)~=' ' && radiusLoc~=L+1         %finds where the radius is in number form in the string and stores it
            radius = radius * 10;           %next digit
            radius = radius +str2num(a(radiusLoc));     %this turns the char to a number
            radiusLoc = radiusLoc +1;
        end
        volume = height * radius^2 *pi;
        fprintf('\nThe volume of the cylinder is %d\n\n',volume);       %does the math and displays
    end
    
    if 1==contains(a,'cone') && 1==count(a,'radius of') && 1==count(a,'height of')%if the string has the word cone and has the reqired information
        heightLoc = strfind(a,'height')+10;
        while a(heightLoc)~=' ' && heightLoc~=L+1            %finds where the hieght is in number form in the string and stores it
            height = height * 10;           %next digit
            height = height +str2num(a(heightLoc));     %this turns the char to a number
            heightLoc = heightLoc +1;
        end
        
        radiusLoc = strfind(a,'radius of')+10;
        while a(radiusLoc)~=' ' && radiusLoc~=L+1            %finds where the radius is in number form in the string and stores it
            radius = radius * 10;           %next digit
            radius = radius +str2num(a(radiusLoc));     %this turns the char to a number
            radiusLoc = radiusLoc +1;
        end
        volume = pi * radius^2 * height / 3;
        fprintf('\nThe volume of the cone is equal to %d\n\n',volume);       %does the math and displays
    end
    
    if 1==contains(a,'cube') && 1==count(a,'height of')%if the string has the word cube and has the reqired information 
        heightLoc = strfind(a,'height')+10;
        while a(heightLoc)~=' ' && heightLoc~=L+1            %finds where the hieght is in number form in the string and stores it
            height = height * 10;           %next digit
            height = height +str2num(a(heightLoc));     %this turns the char to a number
            heightLoc = heightLoc +1;
        end
        volume = height^3;
        fprintf('\nThe volume of the cube is equal to %d\n\n', volume);       %does the math and displays
    end
    
    if 1==contains(a,'sphere') && 1==count(a,'radius of') %if the string has the word sphere and has the reqired information 
        radiusLoc = strfind(a,'radius')+10;
        while a(radiusLoc)~=' ' && radiusLoc~=L+1            %finds where the radius is in number form in the string and stores it
            radius = radius * 10;             %next digit
            radius = radius +str2num(a(radiusLoc));     %this turns the char to a number
            radiusLoc = radiusLoc +1;
        end
        volume = 4/3 * radius^3 * pi;
        fprintf('\nThe volume of the sphere is %d\n\n',volume);       %does the math and displays
    end
    
    
        if (1==contains(a,'sphere')|| 1==contains(a,'cylinder') || 1==contains(a,'cone')) && 1~=contains(a,'radius of')
             disp('could not compute the volume');
        end
        if (1==contains(a,'cube') || 1==contains(a,'cylinder') || 1==contains(a,'cone')) && 1~=contains(a,'height of')
             disp('could not compute the volume');
        end
    a = input(prompt,'s');          %asks again
end
