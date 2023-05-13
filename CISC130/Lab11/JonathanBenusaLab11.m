%Jonathan Benusa
			age = input('Please input your age:');
			fprintf('You are %d years old\n',age);
            months = age * 12;
            fprintf('You are %d months old\n',months);
            weeks = age * 365 / 7;
            fprintf('You are %d weeks old\n',weeks);
            days = age * 365;
            fprintf('You are %d days old\n',days);
            hours = days * 24;
            fprintf('You are %d hours old\n',hours);
            minutes = hours * 60;
            fprintf('You are %d minutes old\n',minutes);
            sec = minutes * 60;
            fprintf('You are %d seconds old\n\n',sec);
            
            weight = input('Please input your weight in pounds:');
            weight = weight / 2.205;
            fprintf('You you weigh %d kg\n\n',weight);
            
            
            %The main difference is that compiled languages need to be
            %compiled before being run. Scripted languages do not need to
            %be run through a compiler before being run. This causes the
            %compiled languages to tipically run faster because they are
            %compiled into the language that the computer usually uses of
            %1's and 0's only once. Scripted languages are compiled each
            %time that the computer gets to each line of code. Also
            %because of this difference, compiled languages show all errors
            %at once right after being compiled whereas scripted languages
            %only show the errors on one line as the code gets to that line
            %while running.
           
            %The advantages of compiling programs is that they give more
            %access to the coding language because they are created from
            %scratch. This allows the the code to do more. Compiled code
            %also has the ability to run on its own with out an interpriter
            %because it is compiled into the computer's language. 
            
            %The advantage of scripting languages are that it is easier to 
            %use and faster to write. Scripted languages are written by
            %combining preexisting components. This also makes them more
            %simple because each function is just a short line. It also
            %doesn't need to be compiled. 
            
            %Sources
            %https://www.educba.com/programming-languages-vs-scripting-languages/
            %https://www.geeksforgeeks.org/whats-the-difference-between-scripting-and-programming-languages/

            