function varargout = untitled(varargin)
% UNTITLED MATLAB code for untitled.fig
%      UNTITLED, by itself, creates a new UNTITLED or raises the existing
%      singleton*.
%
%      H = UNTITLED returns the handle to a new UNTITLED or the handle to
%      the existing singleton*.
%
%      UNTITLED('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in UNTITLED.M with the given input arguments.
%
%      UNTITLED('Property','Value',...) creates a new UNTITLED or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before untitled_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to untitled_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help untitled

% Last Modified by GUIDE v2.5 03-Dec-2018 00:37:58

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @untitled_OpeningFcn, ...
                   'gui_OutputFcn',  @untitled_OutputFcn, ...
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


% --- Executes just before untitled is made visible.
function untitled_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to untitled (see VARARGIN)

% Choose default command line output for untitled
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

axes(handles.axes1);
% Добавление пути для вспомогательных функций

path(path,'Functions');

path_my = cd;
assignin('base','path_my',path_my);

% UIWAIT makes untitled wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = untitled_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

path_my = evalin('base','path_my');
[file, path_my] = uigetfile('*.mat;','Select file',path_my);

if isequal(file,0) 
    return;  
else
    assignin('base','path_my',path_my);
end

axes(handles.axes2);
cla('reset');

axes(handles.axes1);
cla('reset');

set(handles.axes1,'Visible','On');
set(handles.axes2,'Visible','Off');

set(handles.listbox1,'Enable','On');
set(handles.listbox2,'Enable','On');    
set(handles.listbox3,'Enable','On');    


checkboxOff(handles);
checkboxPOIOff(handles);
checkboxNoizeOff(handles);
checkboxStrobOff(handles);

set(handles.checkbox4,'Value',0);
set(handles.checkbox8,'Value',0);
set(handles.checkbox12,'Value',0);
set(handles.checkbox12,'Enable','on');

set(handles.uibuttongroup4,'Visible','off');    
set(handles.uibuttongroup5,'Visible','off');    
set(handles.uibuttongroup6,'Visible','off'); 

set(handles.togglebutton2,'Enable','On');        
set(handles.togglebutton3,'Enable','On');
set(handles.togglebutton5,'Enable','On');
set(handles.togglebutton2,'Value',0);        
set(handles.togglebutton3,'Value',0);
set(handles.togglebutton5,'Value',0);
set(handles.togglebutton4,'Value',0);
set(handles.togglebutton4,'String','3D');

set(handles.text6,'String',file);
informationAssigning(file, path_my);
defaultSetting(handles);

% --- Executes on button press in checkbox1.
function checkbox1_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox1

% Изменение графика в соответствии чекбоксу и меню
toggle2 = get(handles.togglebutton2,'Value');
toggle3 = get(handles.togglebutton3,'Value');
toggle5 = get(handles.togglebutton5,'Value');

realPlot = evalin('base','realPlot');
realIndex = evalin('base','realIndex');

voiPlot = evalin('base','voiPlot');
voiIndex = evalin('base','voiIndex');

hypoPlot = evalin('base','hypoPlot');
hypoIndex = evalin('base','hypoIndex');

if(toggle2 == 1)
    realSize = size(realPlot);
    for i = 1 : realSize(2)
        ch1Plot(handles,realPlot(i));
    end

end

if(toggle3 == 1)
    voiSize = size(voiPlot);
    for i = 1 : voiSize(2)
        ch1Plot(handles,voiPlot(i));
    end

end

if(toggle5 == 1)
    hypoSize = size(hypoPlot);
    for i = 1 : hypoSize(2)
        ch1Plot(handles,hypoPlot(i));
    end

end

if(toggle2 == 0 && toggle3 == 0 && toggle5 == 0)
ch1Plot(handles,voiPlot(voiIndex));
ch1Plot(handles,realPlot(realIndex));
ch1Plot(handles,hypoPlot(hypoIndex));
end

% Update handles structure
guidata(hObject, handles);

% --- Executes on button press in checkbox2.
function checkbox2_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox2

% Изменение графика в соответствии чекбоксу и меню
toggle2 = get(handles.togglebutton2,'Value');
toggle3 = get(handles.togglebutton3,'Value');
toggle5 = get(handles.togglebutton5,'Value');

realPlot = evalin('base','realPlot');
realIndex = evalin('base','realIndex');

voiPlot = evalin('base','voiPlot');
voiIndex = evalin('base','voiIndex');

hypoPlot = evalin('base','hypoPlot');
hypoIndex = evalin('base','hypoIndex');

if(toggle2 == 1)
    realSize = size(realPlot);
    for i = 1 : realSize(2)
        ch2Plot(handles,realPlot(i));
    end

end

if(toggle3 == 1)
    voiSize = size(voiPlot);
    for i = 1 : voiSize(2)
        ch2Plot(handles,voiPlot(i));
    end

end

if(toggle5 == 1)
    hypoSize = size(hypoPlot);
    for i = 1 : hypoSize(2)
        ch2Plot(handles,hypoPlot(i));
    end

end

if(toggle2 == 0 && toggle3 == 0 && toggle5 ==0)
ch2Plot(handles,voiPlot(voiIndex));
ch2Plot(handles,realPlot(realIndex));
ch2Plot(handles,hypoPlot(hypoIndex));
end
% Update handles structure
guidata(hObject, handles);

% --- Executes on button press in checkbox3.
function checkbox3_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox3

toggle2 = get(handles.togglebutton2,'Value');
toggle3 = get(handles.togglebutton3,'Value');
toggle5 = get(handles.togglebutton5,'Value');

realPlot = evalin('base','realPlot');
realIndex = evalin('base','realIndex');

voiPlot = evalin('base','voiPlot');
voiIndex = evalin('base','voiIndex');

hypoPlot = evalin('base','hypoPlot');
hypoIndex = evalin('base','hypoIndex');

if(toggle2 == 1)
    realSize = size(realPlot);
    for i = 1 : realSize(2)
        ch3Plot(handles,realPlot(i));
    end

end

if(toggle3 == 1)
    voiSize = size(voiPlot);
    for i = 1 : voiSize(2)
        ch3Plot(handles,voiPlot(i));
    end

end

if(toggle5 == 1)
    hypoSize = size(hypoPlot);
    for i = 1 : hypoSize(2)
        ch3Plot(handles,hypoPlot(i));
    end

end

if(toggle2 == 0 && toggle3 == 0 && toggle5 == 0)
ch3Plot(handles,voiPlot(voiIndex));
ch3Plot(handles,realPlot(realIndex));
ch3Plot(handles,hypoPlot(hypoIndex));
end

% --- Executes on button press in checkbox4.
function checkbox4_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox4

content = get(hObject,'Value');

POI = evalin('base','POI');

dimentionValue = get(handles.togglebutton4,'Value');
if (dimentionValue == 0)
    if (content == 1)
        poiCheckboxAssignin(POI);
        set(handles.uibuttongroup4,'Visible','on');
    else
        deletePOIPlot();
        checkboxPOIOff(handles);
        set(handles.uibuttongroup4,'Visible','off');
    end
else
    if (content == 1)
        make3D(POI,2);
    else
        poi3dPlot = evalin('base','poi3dPlot');
        delete(poi3dPlot);
    end
end

% --- Executes on button press in checkbox5.
function checkbox5_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox5

checkbox5 = get(handles.checkbox5,'Value');

poiPlot = evalin('base','poiPlot');

if checkbox5 == 1 
    set(poiPlot.ch5,'Visible','on');
else
    set(poiPlot.ch5,'Visible','off');
end


% --- Executes on button press in checkbox6.
function checkbox6_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox6

checkbox6 = get(handles.checkbox6,'Value');

poiPlot = evalin('base','poiPlot');

if checkbox6 == 1 
    set(poiPlot.ch6,'Visible','on');
else
    set(poiPlot.ch6,'Visible','off');
end


% --- Executes on button press in checkbox7.
function checkbox7_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox7

checkbox7 = get(handles.checkbox7,'Value');

poiPlot = evalin('base','poiPlot');

if checkbox7 == 1 
    set(poiPlot.ch7,'Visible','on');
else
    set(poiPlot.ch7,'Visible','off');
end

% --- Executes on button press in checkbox8.
function checkbox8_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox8

dimentionValue = get(handles.togglebutton4,'Value');
content = get(hObject,'Value');
Noize = evalin('base','Noize');

if (dimentionValue == 0)
    if (content == 1)
        noizeCheckboxAssignin(Noize);
        set(handles.uibuttongroup5,'Visible','on');
    else
        deleteNoizePlot();
        checkboxNoizeOff(handles);
        set(handles.uibuttongroup5,'Visible','off');
    end
else
    if (content == 1)
        make3D(Noize,3);
    else
        Noize3dPlot = evalin('base','Noize3dPlot');
        delete(Noize3dPlot);
    end
end


% --- Executes on button press in checkbox9.
function checkbox9_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox9

checkbox9 = get(handles.checkbox9,'Value');

noizePlot = evalin('base','noizePlot');

        if checkbox9 == 1 
            set(noizePlot.ch9,'Visible','on');
        else
            set(noizePlot.ch9,'Visible','off');
        end

% --- Executes on button press in checkbox10.
function checkbox10_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox10

checkbox10 = get(handles.checkbox10,'Value');

noizePlot = evalin('base','noizePlot');

        if checkbox10 == 1 
            set(noizePlot.ch10,'Visible','on');
        else
            set(noizePlot.ch10,'Visible','off');
        end

% --- Executes on button press in checkbox11.
function checkbox11_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox11

checkbox11 = get(handles.checkbox11,'Value');

noizePlot = evalin('base','noizePlot');

        if checkbox11 == 1 
            set(noizePlot.ch11,'Visible','on');
        else
            set(noizePlot.ch11,'Visible','off');
        end
    


% --- Executes on button press in checkbox12.
function checkbox12_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox12

content = get(hObject,'Value');
Strob = evalin('base','Strob');
if (content == 1)
    strobCheckboxAssignin(Strob);
    set(handles.uibuttongroup6,'Visible','on');
else
    deleteStrobPlot();
    checkboxStrobOff(handles);
    set(handles.uibuttongroup6,'Visible','off');
end

% --- Executes on button press in checkbox13.
function checkbox13_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox13 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox13
checkbox13 = get(handles.checkbox13,'Value');

strobPlot = evalin('base','strobPlot');

        if checkbox13 == 1 
            set(strobPlot.ch13,'Visible','on');
        else
            set(strobPlot.ch13,'Visible','off');
        end


% --- Executes on button press in checkbox14.
function checkbox14_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox14 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox14

% Hint: get(hObject,'Value') returns toggle state of checkbox13
checkbox14 = get(handles.checkbox14,'Value');

strobPlot = evalin('base','strobPlot');

        if checkbox14 == 1 
            set(strobPlot.ch14,'Visible','on');
        else
            set(strobPlot.ch14,'Visible','off');
        end


% --- Executes on button press in checkbox15.
function checkbox15_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox15 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox15
checkbox15 = get(handles.checkbox15,'Value');

strobPlot = evalin('base','strobPlot');

        if checkbox15 == 1 
            set(strobPlot.ch15,'Visible','on');
        else
            set(strobPlot.ch15,'Visible','off');
        end
        
% --- Executes on selection change in popupmenu1.
function popupmenu1_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu1

% Изменение пунктов меню и настройка под них графика
contents = get(hObject, 'Value');
POI = get(handles.checkbox4,'Value');
Noize = get(handles.checkbox8,'Value');
Strob = get(handles.checkbox12,'Value');

voiPlot = evalin('base','voiPlot');
voiIndex = evalin('base','voiIndex');
voiSize = size(voiPlot);

realPlot = evalin('base','realPlot');
realIndex = evalin('base','realIndex');
realSize = size(realPlot);

hypoPlot = evalin('base','hypoPlot');
hypoIndex = evalin('base','hypoIndex');
hypoSize = size(hypoPlot);

switch contents 
    case 1
        % Обнуление данных графика(Чекбоксы, рисунок на графике, легенда)
        checkboxOff(handles);
        legend Off;
        for i = 1 : realSize(2)
            setLinesOff(realPlot(i))
        end
        for i = 1 : voiSize(2)
            setLinesOff(voiPlot(i))
        end
        for i = 1 : hypoSize(2)
            setLinesOff(hypoPlot(i))
        end
        % Задаются имя отсчета координат и легенда
        ylabel('Координаты, m');
        legend([realPlot(realIndex).ch1.coordinate,realPlot(realIndex).ch2.coordinate,...
            realPlot(realIndex).ch3.coordinate,...
            voiPlot(voiIndex).ch1.coordinate,voiPlot(voiIndex).ch2.coordinate,...
            voiPlot(voiIndex).ch3.coordinate,...
            hypoPlot(hypoIndex).ch1.coordinate,hypoPlot(hypoIndex).ch2.coordinate,...
            hypoPlot(hypoIndex).ch3.coordinate]);
         % Чекбоксы помех и ПОИ становятся доступны
         set(handles.checkbox4,'Enable','on');
         set(handles.checkbox8,'Enable','on');
         set(handles.checkbox12,'Enable','on');
    case 2
        % Обнуление данных графика(Чекбоксы, рисунок на графике, легенда)
        checkboxOff(handles);
        for i = 1 : realSize(2)
            setLinesOff(realPlot(i))
        end
        for i = 1 : voiSize(2)
            setLinesOff(voiPlot(i))
        end
        for i = 1 : hypoSize(2)
            setLinesOff(hypoPlot(i))
        end
        legend Off;
        % Задаются имя отсчета координат и легенда
        ylabel('Скорость, m/s');
        legend([realPlot(realIndex).ch1.speed,realPlot(realIndex).ch2.speed,realPlot(realIndex).ch3.speed,...
            voiPlot(voiIndex).ch1.speed,voiPlot(voiIndex).ch2.speed,voiPlot(voiIndex).ch3.speed,...
            hypoPlot(hypoIndex).ch1.speed,hypoPlot(hypoIndex).ch2.speed,hypoPlot(hypoIndex).ch3.speed]);
        
        % Чекбокс ПОИ становится недоступен, убирается вся информация о ПОИ
        set(handles.checkbox4,'Enable','off','Value',0);
        if (POI == 1)
            deletePOIPlot();
            checkboxPOIOff(handles);
            set(handles.uibuttongroup4,'Visible','off');
        end
        
        % Чекбокс помех становится недоступен, убирается вся информация о помехах
        set(handles.checkbox8,'Enable','off','Value',0);
        if(Noize == 1)
            deleteNoizePlot();
            checkboxNoizeOff(handles);
            set(handles.uibuttongroup5,'Visible','off');
        end
        
        % Чекбокс строб становится недоступен, убирается вся информация о помехах
        set(handles.checkbox12,'Enable','off','Value',0);
        if(Strob == 1)
            deleteStrobPlot();
            checkboxStrobOff(handles);
            set(handles.uibuttongroup6,'Visible','off');
        end
    case 3
        % Обнуление данных графика(Чекбоксы, рисунок на графике, легенда)
        checkboxOff(handles);
        for i = 1 : realSize(2)
            setLinesOff(realPlot(i))
        end
        for i = 1 : voiSize(2)
            setLinesOff(voiPlot(i))
        end
        for i = 1 : hypoSize(2)
            setLinesOff(hypoPlot(i))
        end
        legend Off;
        % Задаются имя отсчета координат и легенда
        ylabel('Ускорение, m/s^2');
        legend([realPlot(realIndex).ch1.acceleration,realPlot(realIndex).ch2.acceleration,...
            realPlot(realIndex).ch3.acceleration,...
            voiPlot(voiIndex).ch1.acceleration,voiPlot(voiIndex).ch2.acceleration,...
            voiPlot(voiIndex).ch3.acceleration,...
            hypoPlot(hypoIndex).ch1.acceleration,hypoPlot(hypoIndex).ch2.acceleration,...
            hypoPlot(hypoIndex).ch3.acceleration]);
        
        % Чекбокс ПОИ становится недоступен, убирается вся информация о ПОИ
        set(handles.checkbox4,'Enable','off','Value',0);
        if (POI == 1)
            deletePOIPlot();
            checkboxPOIOff(handles);
            set(handles.uibuttongroup4,'Visible','off');
        end
        
        % Чекбокс помех становится недоступен, убирается вся информация о помехах
        set(handles.checkbox8,'Enable','off','Value',0);
        if(Noize == 1)
            deleteNoizePlot();
            checkboxNoizeOff(handles);
            set(handles.uibuttongroup5,'Visible','off');
        end
        
        % Чекбокс строб становится недоступен, убирается вся информация о помехах
        set(handles.checkbox12,'Enable','off','Value',0);
        if(Strob == 1)
            deleteStrobPlot();
            checkboxStrobOff(handles);
            set(handles.uibuttongroup6,'Visible','off');
        end
end

% --- Executes during object creation, after setting all properties.
function popupmenu1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on selection change in listbox1.
function listbox1_Callback(hObject, eventdata, handles)
% hObject    handle to listbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns listbox1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from listbox1
contents = get(hObject,'Value');
dimentionValue = get(handles.togglebutton4,'Value');

if (dimentionValue == 0)
    realPlot = evalin('base','realPlot');
    realSize = size(realPlot);
    for i = 1 : realSize(2)
        setLinesOff(realPlot(i))
    end
    % Привязывание к чекбоксам выбранной цели
    for i = 1:realSize(2)
        if(i == contents)
            realIndex = i;
            assignin('base','realIndex',realIndex);
            makeLegendAfterListbox(handles);
            ch1Plot(handles,realPlot(i));
            ch2Plot(handles,realPlot(i));
            ch3Plot(handles,realPlot(i));
            break;
        end
    end
else
    Real3dPlot = evalin('base','Real3dPlot');
    RealEnd3dPlot = evalin('base','RealEnd3dPlot');
    realSize = size(Real3dPlot);

    set(Real3dPlot,'Visible','off')
    set(RealEnd3dPlot,'Visible','off')

    % Привязывание к чекбоксам выбранной цели
    for i = 1:realSize(2)
        if(i == contents)
            realIndex = i;
            assignin('base','realIndex',realIndex);
            makeLegendAfterListbox(handles);
            set(Real3dPlot(i),'Visible','on');
            set(RealEnd3dPlot(i),'Visible','on');
            break;
        end
    end
end

% --- Executes during object creation, after setting all properties.
function listbox1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to listbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on selection change in listbox2.
function listbox2_Callback(hObject, eventdata, handles)
% hObject    handle to listbox2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns listbox2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from listbox2
contents = get(hObject,'Value');
dimentionValue = get(handles.togglebutton4,'Value');

if (dimentionValue == 0)

    voiPlot = evalin('base','voiPlot');
    voiSize = size(voiPlot);
    for i = 1 : voiSize(2)
        setLinesOff(voiPlot(i))
    end

    % Привязывание к чекбоксам выбранной цели
    for i = 1 : voiSize(2)
        if(i == contents)
            voiIndex = i;
            assignin('base','voiIndex',voiIndex);
            makeLegendAfterListbox(handles);
            ch1Plot(handles,voiPlot(i));
            ch2Plot(handles,voiPlot(i));
            ch3Plot(handles,voiPlot(i));
            break;
        end
    end
else
    Voi3dPlot = evalin('base','Voi3dPlot');
    VoiEnd3dPlot = evalin('base','VoiEnd3dPlot');
    voiSize = size(Voi3dPlot);
    
    set(Voi3dPlot,'Visible','off');
    set(VoiEnd3dPlot,'Visible','off');
    % Привязывание к чекбоксам выбранной цели
    for i = 1:voiSize(2)
        if(i == contents)
            voiIndex = i;
            assignin('base','voiIndex',voiIndex);
            makeLegendAfterListbox(handles);
            set(Voi3dPlot(i),'Visible','on');
            set(VoiEnd3dPlot(i),'Visible','on');
            break;
        end
    end
end




% --- Executes during object creation, after setting all properties.
function listbox2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to listbox2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in listbox3.
function listbox3_Callback(hObject, eventdata, handles)
% hObject    handle to listbox3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns listbox3 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from listbox3
contents = get(hObject,'Value');
dimentionValue = get(handles.togglebutton4,'Value');

if (dimentionValue == 0)
    hypoPlot = evalin('base','hypoPlot');
    hypoSize = size(hypoPlot);
    for i = 1 : hypoSize(2)
        setLinesOff(hypoPlot(i))
    end

    % Привязывание к чекбоксам выбранной цели
    for i = 1:hypoSize(2)
        if(i == contents)
            hypoIndex = i;
            assignin('base','hypoIndex',hypoIndex);
            makeLegendAfterListbox(handles);
            ch1Plot(handles,hypoPlot(i));
            ch2Plot(handles,hypoPlot(i));
            ch3Plot(handles,hypoPlot(i));
            break;
        end
    end
else
    Hypo3dPlot = evalin('base','Hypo3dPlot');
    HypoEnd3dPlot = evalin('base','HypoEnd3dPlot');
    hypoSize = size(Hypo3dPlot);

    set(Hypo3dPlot,'Visible','off')
    set(HypoEnd3dPlot,'Visible','off')

    % Привязывание к чекбоксам выбранной цели
    for i = 1:hypoSize(2)
        if(i == contents)
            hypoIndex = i;
            assignin('base','hypoIndex',hypoIndex);
            makeLegendAfterListbox(handles);
            set(Hypo3dPlot(i),'Visible','on');
            set(HypoEnd3dPlot(i),'Visible','on');
            break;
        end
    end
end


% --- Executes during object creation, after setting all properties.
function listbox3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to listbox3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in togglebutton2.
function togglebutton2_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of togglebutton2
content = get(hObject,'Value');
dimentionValue = get(handles.togglebutton4,'Value');

realPlot = evalin('base','realPlot');
realSize = size(realPlot);
realIndex = evalin('base','realIndex');

if (dimentionValue == 0)
    voiPlot = evalin('base','voiPlot');
    voiSize = size(voiPlot);
    voiIndex = evalin('base','voiIndex');
    
    hypoPlot = evalin('base','hypoPlot');
    hypoSize = size(hypoPlot);
    hypoIndex = evalin('base','hypoIndex');
    if (content == 1)
        linesOff();
        for i = 1 : realSize(2)
            ch1Plot(handles,realPlot(i));
            ch2Plot(handles,realPlot(i));
            ch3Plot(handles,realPlot(i));
        end
        set(handles.listbox1,'Enable','Off');
        set(handles.listbox2,'Enable','Off');
        set(handles.listbox3,'Enable','Off');
        set(handles.togglebutton3,'Enable','Off');
        set(handles.togglebutton5,'Enable','Off');
        
    else
        for i = 1 : realSize(2)
            if(realIndex == i)
                continue;
            end
            setLinesOff(realPlot(i))
        end
        for i = 1 : voiSize(2)
            if(voiIndex == i)
                ch1Plot(handles,voiPlot(i));
                ch2Plot(handles,voiPlot(i));
                ch3Plot(handles,voiPlot(i));
                break;
            end
        end
        for i = 1 : hypoSize(2)
            if(hypoIndex == i)
                ch1Plot(handles,hypoPlot(i));
                ch2Plot(handles,hypoPlot(i));
                ch3Plot(handles,hypoPlot(i));
                break;
            end
        end
        set(handles.listbox1,'Enable','On');
        set(handles.listbox2,'Enable','On');
        set(handles.listbox3,'Enable','On');
        set(handles.togglebutton3,'Enable','On');
        set(handles.togglebutton5,'Enable','On');
    end
else
    Real3dPlot = evalin('base','Real3dPlot');
    RealEnd3dPlot = evalin('base','RealEnd3dPlot');
    if (content == 1)
        set(handles.listbox1,'Enable','off');
        set(Real3dPlot,'Visible','on');
        set(RealEnd3dPlot,'Visible','on');
    else 
        set(handles.listbox1,'Enable','On');
        
        set(Real3dPlot,'Visible','off');
        set(RealEnd3dPlot,'Visible','off');
        
        for i = 1:realSize(2)
            if(i == realIndex)
                set(Real3dPlot(i),'Visible','on');
                set(RealEnd3dPlot(i),'Visible','on');
                break;
            end
        end
    end
end


% --- Executes on button press in togglebutton3.
function togglebutton3_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of togglebutton3

content = get(hObject,'Value');

voiPlot = evalin('base','voiPlot');
voiIndex = evalin('base','voiIndex');
voiSize = size(voiPlot);

dimentionValue = get(handles.togglebutton4,'Value');
if (dimentionValue == 0)
    realPlot = evalin('base','realPlot');
    realSize = size(realPlot);
    realIndex = evalin('base','realIndex');

    hypoPlot = evalin('base','hypoPlot');
    hypoSize = size(hypoPlot);
    hypoIndex = evalin('base','hypoIndex');
    
    if (content == 1)
        linesOff();
        for i = 1 : voiSize(2)
            ch1Plot(handles,voiPlot(i));
            ch2Plot(handles,voiPlot(i));
            ch3Plot(handles,voiPlot(i));
        end
        set(handles.listbox1,'Enable','Off');
        set(handles.listbox2,'Enable','Off');
        set(handles.listbox3,'Enable','Off');
        set(handles.togglebutton2,'Enable','Off');
        set(handles.togglebutton5,'Enable','Off');
    else
        for i = 1 : voiSize(2)
            if(voiIndex == i)
                continue;
            end
            setLinesOff(voiPlot(i))
        end
        for i = 1 : realSize(2)
            if(realIndex == i)
                ch1Plot(handles,realPlot(i));
                ch2Plot(handles,realPlot(i));
                ch3Plot(handles,realPlot(i));
                break;
            end
        end
        for i = 1 : hypoSize(2)
            if(hypoIndex == i)
                ch1Plot(handles,hypoPlot(i));
                ch2Plot(handles,hypoPlot(i));
                ch3Plot(handles,hypoPlot(i));
                break;
            end
        end
        set(handles.listbox1,'Enable','On');
        set(handles.listbox2,'Enable','On');
        set(handles.listbox3,'Enable','On');
        set(handles.togglebutton2,'Enable','On');
        set(handles.togglebutton5,'Enable','On');
    end
else
    Voi3dPlot = evalin('base','Voi3dPlot');
    VoiEnd3dPlot = evalin('base','VoiEnd3dPlot');
    if (content == 1)
        set(handles.listbox2,'Enable','off');
        set(Voi3dPlot,'Visible','on');
        set(VoiEnd3dPlot,'Visible','on');
    else 
        
        set(handles.listbox2,'Enable','On');
        set(Voi3dPlot,'Visible','off');
        set(VoiEnd3dPlot,'Visible','off');
        
        for i = 1:voiSize(2)
            if(i == voiIndex)
                set(Voi3dPlot(i),'Visible','on');
                set(VoiEnd3dPlot(i),'Visible','on');
                break;
            end
        end
    end  
end

% --- Executes on button press in togglebutton5.
function togglebutton5_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of togglebutton5
content = get(hObject,'Value');

dimentionValue = get(handles.togglebutton4,'Value');


hypoPlot = evalin('base','hypoPlot');
hypoIndex = evalin('base','hypoIndex');
hypoSize = size(hypoPlot);
if (dimentionValue == 0)
    realPlot = evalin('base','realPlot');
    realSize = size(realPlot);
    realIndex = evalin('base','realIndex');

    voiPlot = evalin('base','voiPlot');
    voiSize = size(voiPlot);
    voiIndex = evalin('base','voiIndex');
    if (content == 1)
        linesOff();
        for i = 1 : hypoSize(2)
            ch1Plot(handles,hypoPlot(i));
            ch2Plot(handles,hypoPlot(i));
            ch3Plot(handles,hypoPlot(i));
        end
        set(handles.listbox1,'Enable','Off');
        set(handles.listbox2,'Enable','Off');
        set(handles.listbox3,'Enable','Off');
        set(handles.togglebutton2,'Enable','Off');
        set(handles.togglebutton3,'Enable','Off');
    else
        for i = 1 : hypoSize(2)
            if(hypoIndex == i)
                continue;
            end
            setLinesOff(hypoPlot(i))
        end
        for i = 1 : realSize(2)
            if(realIndex == i)
                ch1Plot(handles,realPlot(i));
                ch2Plot(handles,realPlot(i));
                ch3Plot(handles,realPlot(i));
                break;
            end
        end
        for i = 1 : voiSize(2)
            if(voiIndex == i)
                ch1Plot(handles,voiPlot(i));
                ch2Plot(handles,voiPlot(i));
                ch3Plot(handles,voiPlot(i));
                break;
            end
        end
        set(handles.listbox1,'Enable','On');
        set(handles.listbox2,'Enable','On');
        set(handles.listbox3,'Enable','On');
        set(handles.togglebutton2,'Enable','On');
        set(handles.togglebutton3,'Enable','On');
    end
else
    Hypo3dPlot = evalin('base','Hypo3dPlot');
    HypoEnd3dPlot = evalin('base','HypoEnd3dPlot');
    if (content == 1)
        set(handles.listbox3,'Enable','off');
        set(Hypo3dPlot,'Visible','on');
        set(HypoEnd3dPlot,'Visible','on');
    else 
        set(handles.listbox3,'Enable','On');
        
        set(Hypo3dPlot,'Visible','off');
        set(HypoEnd3dPlot,'Visible','off');
        
        for i = 1:hypoSize(2)
            if(i == hypoIndex)
                set(Hypo3dPlot(i),'Visible','on');
                set(HypoEnd3dPlot(i),'Visible','on');
                break;
            end
        end
    end
end

% --- Executes on button press in togglebutton4.
function togglebutton4_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
value = get(hObject,'Value');
    
try
   poiPlot = evalin('base','poiPlot');
   deletePOIPlot();
catch
end

try
   noizePlot = evalin('base','noizePlot');
   deleteNoizePlot();
catch
end

try
   strobPlot = evalin('base','strobPlot');
   deleteStrobPlot();
catch
end

if (value == 1)
    legend('off');
    axes(handles.axes2);
    set(hObject,'String','2D');
    
    set(handles.axes2,'Visible','On');
    set(handles.axes1,'Visible','Off');
    
    checkboxOff(handles);
    checkboxPOIOff(handles);
    checkboxNoizeOff(handles);
    checkboxStrobOff(handles);
    
    set(handles.checkbox4,'Value',0);
    set(handles.checkbox8,'Value',0);
    set(handles.checkbox12,'Value',0);
    set(handles.checkbox12,'Enable','Off');
    
    set(handles.uibuttongroup1,'Visible','Off')
    set(handles.uibuttongroup4,'Visible','off');    
    set(handles.uibuttongroup5,'Visible','off');    
    set(handles.uibuttongroup6,'Visible','off');
    
    set(handles.togglebutton2,'Enable','On');        
    set(handles.togglebutton3,'Enable','On');
    set(handles.togglebutton5,'Enable','On');
    set(handles.togglebutton2,'Value',0);        
    set(handles.togglebutton3,'Value',0);
    set(handles.togglebutton5,'Value',0);
    
    Real = evalin('base','Real');
    make3DReal(Real,value);
    Hypo = evalin('base','Hypo');
    make3DHypo(Hypo,value);
    VOI = evalin('base','VOI');
    make3DVOI(VOI,value);
    
    Real3dPlot = evalin('base','Real3dPlot');
    RealEnd3dPlot = evalin('base','RealEnd3dPlot');
    Hypo3dPlot = evalin('base','Hypo3dPlot');
    HypoEnd3dPlot = evalin('base','HypoEnd3dPlot');
    Voi3dPlot = evalin('base','Voi3dPlot');
    VoiEnd3dPlot = evalin('base','VoiEnd3dPlot');
    
    realIndex = 1;
    voiIndex = 1;
    hypoIndex = 1;
    
    assignin('base','realIndex',realIndex);
    assignin('base','voiIndex',voiIndex);
    assignin('base','hypoIndex',hypoIndex);
    
    legend([Real3dPlot(1),RealEnd3dPlot(1),Hypo3dPlot(1),HypoEnd3dPlot(1),...
        Voi3dPlot(1),VoiEnd3dPlot(1)]);
else 
    Real = evalin('base','Real');
    make3DReal(Real,value);
    
    Hypo = evalin('base','Hypo');
    make3DHypo(Hypo,value);
    
    VOI = evalin('base','VOI');
    make3DVOI(VOI,value);
    
    cla('reset');
    set(hObject,'String','3D');
    axes(handles.axes1);
    
    realPlot = evalin('base','realPlot');
    voiPlot = evalin('base','voiPlot');
    hypoPlot = evalin('base','hypoPlot');
    legend([realPlot(1).ch1.coordinate,realPlot(1).ch2.coordinate,realPlot(1).ch3.coordinate,...
        voiPlot(1).ch1.coordinate,voiPlot(1).ch2.coordinate,voiPlot(1).ch3.coordinate,...
        hypoPlot(1).ch1.coordinate,hypoPlot(1).ch2.coordinate,hypoPlot(1).ch3.coordinate]);
    
    set(handles.axes1,'Visible','On');
    set(handles.axes2,'Visible','Off');
    
    set(handles.uibuttongroup1,'Visible','On');
    set(handles.uibuttongroup7,'Visible','On');
    
    set(handles.checkbox12,'Enable','On');
    set(handles.checkbox4,'Value',0);
    set(handles.checkbox8,'Value',0);
    set(handles.checkbox12,'Value',0);
    
    set(handles.togglebutton2,'Value',0);        
    set(handles.togglebutton3,'Value',0);
    set(handles.togglebutton5,'Value',0);
    set(handles.togglebutton2,'Enable','On');        
    set(handles.togglebutton3,'Enable','On');
    set(handles.togglebutton5,'Enable','On');
    
    realIndex = 1;
    voiIndex = 1;
    hypoIndex = 1;
    
    assignin('base','realIndex',realIndex);
    assignin('base','voiIndex',voiIndex);
    assignin('base','hypoIndex',hypoIndex);
end

%TODO: Добавить удаление графиков эталона вои и гипотез при переходе на 3d
%TODO: Возможность включать и выключать некоторые графики полностью вместе
%с другими