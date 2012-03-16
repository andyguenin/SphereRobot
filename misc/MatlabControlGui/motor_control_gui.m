function motor_control_gui
% For controlling the functional prototype.

% direction on b2
% enable on b7
delete(instrfindall);
close all;
clear all;
clc;


h = serial('COM4', 'Baudrate', 9600);
disp('Connected to MAEVARM');
fopen(h);
disp('Opened MAEVARM');
t = timer('TimerFcn', @stimeout, 'StartDelay', 0.3);
isset = 0;
dir = 0;

   %  Create and then hide the GUI as it is being constructed.
   f = figure('Visible','off','Position',[720,500,450,450]);
   backgroundColor = 'w';
   set(gcf, 'Color', backgroundColor);
   
   %  Construct the components.
   h_up = uicontrol('Style','pushbutton','String','Motor Up',...
          'Position',[-320,300,140,50],...
          'Callback',{@upbutton_Callback});
      %Create up arrow symbol
      x = [.3,.3];
      y = [.68,.76];       
      uparr = annotation('arrow',x,y);
      
   h_down = uicontrol('Style','pushbutton','String','Motor Down',...
          'Position',[-320,100,140,50],...
          'Callback',{@downbutton_Callback});
      %Create down arrow symbol
      x = [.3,.3];
      y = [.32,.24];       
      downarr = annotation('arrow',x,y);
   
      
   htext1 = uicontrol('Style','text','String','Motor Control',...
          'Position',[-320,400,120,30], 'FontSize', 18,'BackgroundColor','w');
   htext2 = uicontrol('Style','text','String','Push Button for Control',...
          'Position',[650,210,120,30], 'FontSize', 14, 'BackgroundColor','w');
   
      hpopup = uicontrol('Style', 'popupmenu', 'String', {'12.5', '25', '37.5', '50', '62.5', '75', '87.5', '100'}, ...
          'Position', [-320, 50, 120, 30], 'Callback', {@popup_Callback});
         h_stop = uicontrol('Style','pushbutton','String','Toggle',...
          'Position',[0,200,140,50],...
          'Callback',{@stopbutton_Callback});
  
   align([h_up,h_stop, h_down,htext1,htext2, hpopup],'Center','None');
  
   
   % Initialize the GUI.
   % Change units to normalized so components resize 
   % automatically.
   set([f,h_up,h_down,htext1,htext2],...
   'Units','normalized');
   
   % Start the motor off
    motor_off = true;5
    current_data = motor_off;
 
   % Assign the GUI a name to appear in the window title.
   set(f,'Name','Motor Control')
   % Move the GUI to the center of the screen.
   movegui(f,'center')
   % Make the GUI visible.
   set(f,'Visible','on');
 
   %  Callbacks for simple_gui. 
   % Push button callbacks.
 
   function upbutton_Callback(source,eventdata)
       if isset == 0
           isset = 1;
           dir = 1;
       else
           if dir == 0
            fwrite(h, 1);
            start(t);
            dir = 1;
           end
       end
   end
 
   function downbutton_Callback(source,eventdata) 
       if isset == 0
           isset = 1;
           dir = 0;
       else
           if dir == 1
               fwrite(h, 2);
               start(t);
               dir = 0;
           end
       end
   end

function stopbutton_Callback(source,eventdata) 
    if isset == 1
        if dir == 0
            upbutton_Callback(source, eventdata)
        else
            downbutton_Callback(source, eventdata);
        end
    end
end

    function popup_Callback(source, eventdata)
       str = get(source, 'String');
       val = get(source, 'Value');
        fwrite(h, str2num(str{val})); 
    end

    function stimeout(obj, event)
        stop();
    end

    function stop()
        fwrite(h,3);
    end
end 