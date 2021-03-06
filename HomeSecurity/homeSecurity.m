function varargout = homeSecurity(varargin)
% HOMESECURITY MATLAB code for homeSecurity.fig
%      HOMESECURITY, by itself, creates a new HOMESECURITY or raises the existing
%      singleton*.
%
%      H = HOMESECURITY returns the handle to a new HOMESECURITY or the handle to
%      the existing singleton*.
%
%      HOMESECURITY('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in HOMESECURITY.M with the given input arguments.
%
%      HOMESECURITY('Property','Value',...) creates a new HOMESECURITY or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before homeSecurity_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to homeSecurity_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help homeSecurity

% Last Modified by GUIDE v2.5 03-Feb-2018 21:14:42

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @homeSecurity_OpeningFcn, ...
    'gui_OutputFcn',  @homeSecurity_OutputFcn, ...
    'gui_LayoutFcn',  [] , ...
    'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before homeSecurity is made visible.
function homeSecurity_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to homeSecurity (see VARARGIN)

% Choose default command line output for homeSecurity
handles.output = hObject;

% Initial Variables
handles.startedFlag = 0;
handles.enMail = 0;
handles.enAlarm = 0;
handles.enStorage = 0;
handles.targetCount = 0;
handles.Fs = 0;
% Update handles structure
guidata(hObject, handles);

% UIWAIT makes homeSecurity wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = homeSecurity_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of pushbutton1
button_state1 = get(hObject,'Value');
if button_state1 == 0
    clear sound
    display('Disabled!');
    set(handles.pushbutton1,'string','START','enable','on','BackgroundColor','red');
    if handles.startedFlag == 1
        display('Camera OFF!');
        imaqreset
    end
    
else
    display('Activated! Camera:ON');
    set(handles.pushbutton1,'string','STOP','enable','on','BackgroundColor','green');
    handles.startedFlag = 1;
    mycam = webcam(2);
    runFrameCount = str2num(get(handles.edit7,'string'));
    targetPixelTHold = str2num(get(handles.edit5,'string'));
    shadeTHold = str2num(get(handles.edit6,'string'));
    storageDir = get(handles.edit3,'string');
    destinationMail = get(handles.edit8,'string');
    
    for i=1:runFrameCount
        
        button_state1 = get(hObject,'Value');
        if button_state1 == 0
            break;
        end
        
        imgCaptured1 = snapshot(mycam);
        imgCaptured2 = snapshot(mycam);
        
        imshow(imgCaptured2, 'Parent', handles.axes1);
        
        diffLeftAndRightGray = imabsdiff(rgb2gray(imgCaptured1),rgb2gray(imgCaptured2));
        diffTHoldGray = diffLeftAndRightGray>shadeTHold;
        bboxes = regionprops(diffTHoldGray,'BoundingBox');
        
        imshow(diffTHoldGray, 'Parent', handles.axes2);
        
        if(i>1)
            
            for k=1:length(bboxes)
                CurrBB = bboxes(k).BoundingBox;
                if(CurrBB(3)>targetPixelTHold) && (CurrBB(4)>targetPixelTHold)
                    handles.targetCount = handles.targetCount + 1;
                    set(handles.edit4,'String',num2str(handles.targetCount));
                    
                    s = num2str(clock);
                    
                    axes(handles.axes2);
                    rectangle('Position', [CurrBB(1),CurrBB(2),CurrBB(3),CurrBB(4)],'EdgeColor','m','LineWidth',3)
                    
                    if(handles.enMail == 1)
                        %Send E-Mail
                        imwrite(imgCaptured2,strcat(s,'.jpg'),'jpg','Comment','My JPEG file');
                        sendmail(destinationMail,'Target Found',s,strcat(s,'.jpg'));
                    end
                    
                    if(handles.enStorage == 1)
                        %Send E-Mail                   
                        imwrite(imgCaptured2,strcat(storageDir,'\',s,'.jpg'),'jpg','Comment','My JPEG file');
                    end
                    
                    if (handles.targetCount == 2) && (handles.enAlarm == 1)
                        %Play Alarm
                        sound(handles.Alarm,handles.Fs);
                    end
                end
            end
        end
        imshow(diffTHoldGray)
    end
end

guidata(hObject,handles);

% --- Executes on button press in togglebutton1.
function togglebutton1_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of togglebutton1


% --- Executes on button press in togglebutton2.
function togglebutton2_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of togglebutton2
button_state2 = get(hObject,'Value');
if button_state2 == 0
    display('Alarm:OFF!');
    set(handles.togglebutton2,'string','ALARM ON','enable','on','BackgroundColor','red');
    handles.enAlarm = 0;
else
    set(handles.togglebutton2,'string','ALARM OFF','enable','on','BackgroundColor','green');
    %% Audio Import
    display('Alarm:ON!');
    [handles.Alarm,handles.Fs] = audioread('alarm.mp3');
    handles.enAlarm = 1;
end

guidata(hObject,handles);

% --- Executes on button press in togglebutton3.
function togglebutton3_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of togglebutton3


% --- Executes on button press in pushbutton4.
function pushbutton4_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

eMailPassword = passdlg();
eMailPasswordChar = char(eMailPassword(1).Pass);
if (~isempty(eMailPasswordChar))
    eMailAddress = get(handles.edit1,'string');
    set(handles.pushbutton4,'string','Password Entered','enable','on','BackgroundColor','green');
    handles.enMail = 1;
    setpref('Internet','SMTP_Server','smtp.gmail.com');
    setpref('Internet','E_mail',eMailAddress);
    setpref('Internet','SMTP_Username',eMailAddress);
    setpref('Internet','SMTP_Password',eMailPasswordChar);
    props = java.lang.System.getProperties;
    props.setProperty('mail.smtp.auth','true');
    props.setProperty('mail.smtp.socketFactory.class','javax.net.ssl.SSLSocketFactory');
    props.setProperty('mail.smtp.socketFactory.port','465');
end
guidata(hObject,handles);

% --- Executes on key press with focus on pushbutton4 and none of its controls.
function pushbutton4_KeyPressFcn(hObject, eventdata, handles)
% hObject    handle to pushbutton4 (see GCBO)
% eventdata  structure with the following fields (see MATLAB.UI.CONTROL.UICONTROL)
%	Key: name of the key that was pressed, in lower case
%	Character: character interpretation of the key(s) that was pressed
%	Modifier: name(s) of the modifier key(s) (i.e., control, shift) pressed
% handles    structure with handles and user data (see GUIDATA)


function edit3_Callback(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit3 as text
%        str2double(get(hObject,'String')) returns contents of edit3 as a double


% --- Executes during object creation, after setting all properties.
function edit3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit4_Callback(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit4 as text
%        str2double(get(hObject,'String')) returns contents of edit4 as a double


% --- Executes during object creation, after setting all properties.
function edit4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit5_Callback(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit5 as text
%        str2double(get(hObject,'String')) returns contents of edit5 as a double


% --- Executes during object creation, after setting all properties.
function edit5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function edit6_Callback(hObject, eventdata, handles)
% hObject    handle to edit6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit6 as text
%        str2double(get(hObject,'String')) returns contents of edit6 as a double


% --- Executes during object creation, after setting all properties.
function edit6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit7_Callback(hObject, eventdata, handles)
% hObject    handle to edit7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit7 as text
%        str2double(get(hObject,'String')) returns contents of edit7 as a double


% --- Executes during object creation, after setting all properties.
function edit7_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in togglebutton6.
function togglebutton6_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of togglebutton6

button_state3 = get(hObject,'Value');
if button_state3 == 0
    display('Storage:OFF!');
    set(handles.togglebutton6,'string','STORAGE ON','enable','on','BackgroundColor','red');
    handles.enStorage = 0;
else
    set(handles.togglebutton6,'string','STORAGE OFF','enable','on','BackgroundColor','green');
    %% Audio Import
    display('Storage:ON!');
    handles.enStorage = 1;
end

guidata(hObject,handles);



function edit8_Callback(hObject, eventdata, handles)
% hObject    handle to edit8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit8 as text
%        str2double(get(hObject,'String')) returns contents of edit8 as a double


% --- Executes during object creation, after setting all properties.
function edit8_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
