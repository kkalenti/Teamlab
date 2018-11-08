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

% Last Modified by GUIDE v2.5 04-Nov-2018 16:28:52

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

defaultSetting(handles);


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

% --- Executes on button press in checkbox1.
function checkbox1_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox1

% Изменение графика в соответствии чекбоксу и меню
checkbox1 = get(handles.checkbox1,'Value');
contents = get(handles.popupmenu1, 'Value');

realPlot = evalin('base','realPlot');
voiPlot = evalin('base','voiPlot');

switch contents 
    case 1
        if checkbox1 == 1 
            set(realPlot.ch1.coordinate,'Visible','on');
            set(voiPlot.ch1.coordinate,'Visible','on');
        else
            set(realPlot.ch1.coordinate,'Visible','off');
            set(voiPlot.ch1.coordinate,'Visible','off');
        end
    case 2
        if checkbox1 == 1 
            set(realPlot.ch1.speed,'Visible','on');
            set(voiPlot.ch1.speed,'Visible','on');
        else
            set(realPlot.ch1.speed,'Visible','off');
            set(voiPlot.ch1.speed,'Visible','off');
        end
    case 3
        if checkbox1 == 1 
            set(realPlot.ch1.acceleration,'Visible','on');
            set(voiPlot.ch1.acceleration,'Visible','on');
        else
            set(realPlot.ch1.acceleration,'Visible','off');
            set(voiPlot.ch1.acceleration,'Visible','off');
        end
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
checkbox2 = get(handles.checkbox2,'Value');
contents = get(handles.popupmenu1, 'Value');

realPlot = evalin('base','realPlot');
voiPlot = evalin('base','voiPlot');

switch contents 
    case 1
        if checkbox2 == 1 
            set(realPlot.ch2.coordinate,'Visible','on');
            set(voiPlot.ch2.coordinate,'Visible','on');
        else
            set(realPlot.ch2.coordinate,'Visible','off');
            set(voiPlot.ch2.coordinate,'Visible','off');
        end
    case 2
        if checkbox2 == 1 
            set(realPlot.ch2.speed,'Visible','on');
            set(voiPlot.ch2.speed,'Visible','on');
        else
            set(realPlot.ch2.speed,'Visible','off');
            set(voiPlot.ch2.speed,'Visible','off');
        end
    case 3
        if checkbox2 == 1 
            set(realPlot.ch2.acceleration,'Visible','on');
            set(voiPlot.ch2.acceleration,'Visible','on');
        else
            set(realPlot.ch2.acceleration,'Visible','off');
            set(voiPlot.ch2.acceleration,'Visible','off');
        end
end
% Update handles structure
guidata(hObject, handles);

% --- Executes on button press in checkbox3.
function checkbox3_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox3

% Изменение графика в соответствии чекбоксу и меню
checkbox3 = get(handles.checkbox3,'Value');
contents = get(handles.popupmenu1, 'Value');

realPlot = evalin('base','realPlot');
voiPlot = evalin('base','voiPlot');

switch contents 
    case 1
        if checkbox3 == 1 
            set(realPlot.ch3.coordinate,'Visible','on');
            set(voiPlot.ch3.coordinate,'Visible','on');
        else
            set(realPlot.ch3.coordinate,'Visible','off');
            set(voiPlot.ch3.coordinate,'Visible','off');
        end
    case 2
        if checkbox3 == 1 
            set(realPlot.ch3.speed,'Visible','on');
            set(voiPlot.ch3.speed,'Visible','on');
        else
            set(realPlot.ch3.speed,'Visible','off');
            set(voiPlot.ch3.speed,'Visible','off');
        end
    case 3
        if checkbox3 == 1 
            set(realPlot.ch3.acceleration,'Visible','on');
            set(voiPlot.ch3.acceleration,'Visible','on');
        else
            set(realPlot.ch3.acceleration,'Visible','off');
            set(voiPlot.ch3.acceleration,'Visible','off');
        end
end

% --- Executes on button press in checkbox4.
function checkbox4_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox4

content = get(hObject,'Value');
POI = evalin('base','POI');
if (content == 1)
    poiCheckboxAssignin(POI);
    set(handles.uibuttongroup4,'Visible','on');
else
    deletePOIPlot();
    checkboxPOIOff(handles);
    set(handles.uibuttongroup4,'Visible','off');
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
    set(poiPlot.ch5.coordinate,'Visible','on');
else
    set(poiPlot.ch5.coordinate,'Visible','off');
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
    set(poiPlot.ch6.coordinate,'Visible','on');
else
    set(poiPlot.ch6.coordinate,'Visible','off');
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
    set(poiPlot.ch7.coordinate,'Visible','on');
else
    set(poiPlot.ch7.coordinate,'Visible','off');
end

% --- Executes on button press in checkbox8.
function checkbox8_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox8

content = get(hObject,'Value');
Noize = evalin('base','Noize');
if (content == 1)
    noizeCheckboxAssignin(Noize);
    set(handles.uibuttongroup5,'Visible','on');
else
    deleteNoizePlot();
    checkboxNoizeOff(handles);
    set(handles.uibuttongroup5,'Visible','off');
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
            set(noizePlot.ch9.coordinate,'Visible','on');
        else
            set(noizePlot.ch9.coordinate,'Visible','off');
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
            set(noizePlot.ch10.coordinate,'Visible','on');
        else
            set(noizePlot.ch10.coordinate,'Visible','off');
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
            set(noizePlot.ch11.coordinate,'Visible','on');
        else
            set(noizePlot.ch11.coordinate,'Visible','off');
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

realPlot = evalin('base','realPlot');
voiPlot = evalin('base','voiPlot');
switch contents 
    case 1
        checkboxOff(handles);
        linesOff();
        legendOff();
        checkboxCoordinateName(handles);
        legend([realPlot.ch1.coordinate,realPlot.ch2.coordinate,realPlot.ch3.coordinate,...
             voiPlot.ch1.coordinate,voiPlot.ch2.coordinate,voiPlot.ch3.coordinate,],...
             'Эталон x','Эталон y','Эталон z','ВОИ x','ВОИ y','ВОИ z' );
         set(handles.checkbox4,'Enable','on');
         set(handles.checkbox8,'Enable','on');
    case 2
        checkboxOff(handles);
        linesOff();
        legendOff();
        checkboxSpeedName(handles);
        legend([realPlot.ch1.speed,realPlot.ch2.speed,realPlot.ch3.speed,...
            voiPlot.ch1.speed,voiPlot.ch2.speed,voiPlot.ch3.speed,],...
            'Эталон Vx','Эталон Vy','Эталон Vz','ВОИ Vx','ВОИ Vy','ВОИ Vz' );
        
        set(handles.checkbox4,'Enable','off','Value',0);
        deletePOIPlot();
        checkboxPOIOff(handles);
        set(handles.uibuttongroup4,'Visible','off');
        
        set(handles.checkbox8,'Enable','off','Value',0);
        deleteNoizePlot();
        checkboxNoizeOff(handles);
        set(handles.uibuttongroup5,'Visible','off');
    case 3
        checkboxOff(handles);
        linesOff();
        legendOff();
        checkboxAccelerateName(handles);
        legend([realPlot.ch1.acceleration,realPlot.ch2.acceleration,realPlot.ch3.acceleration,...
            voiPlot.ch1.acceleration,voiPlot.ch2.acceleration,voiPlot.ch3.acceleration,],...
            'Эталон ax','Эталон ay','Эталон az','ВОИ ax','ВОИ ay','ВОИ az' );
        set(handles.checkbox4,'Enable','off','Value',0);
        deletePOIPlot();
        checkboxPOIOff(handles);
        set(handles.uibuttongroup4,'Visible','off');
        
        set(handles.checkbox8,'Enable','off','Value',0);
        deleteNoizePlot();
        checkboxNoizeOff(handles);
        set(handles.uibuttongroup5,'Visible','off');
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

Real = evalin('base', 'Real');
realSize = size(Real);
    linesOff();
    checkboxOff(handles);
    for i = 1:realSize(2)
        if(i == contents)
            realCheckboxAssignin(Real(i));
            makeLegendAfterListbox(handles);
            break;
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

VOI = evalin('base', 'VOI');
voiSize = size(VOI);
    linesOff();
    checkboxOff(handles);
    for i = 1 : voiSize(2)
        if(i == contents)
            voiCheckboxAssignin(VOI(i));
            makeLegendAfterListbox(handles);
            break;
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

% --- Создание графиков и привязка их к определенным чекбоксам
function realCheckboxAssignin(Real)
real.ch1.coordinate = plot(Real.t(:),Real.x(:),'--og','Visible','off','DisplayName', 'x');
real.ch1.speed = plot(Real.t(:),Real.Vx(:),'--og','Visible','off','DisplayName', 'V(x)');
real.ch1.acceleration = plot(Real.t(:),Real.ax(:),'--og','Visible','off','DisplayName', 'a(x)');

real.ch2.coordinate = plot(Real.t(:),Real.y(:),'--or','Visible','off','DisplayName', 'y');
real.ch2.speed = plot(Real.t(:),Real.Vy(:),'--or','Visible','off','DisplayName', 'V(y)');
real.ch2.acceleration = plot(Real.t(:),Real.ay(:),'--or','Visible','off','DisplayName', 'a(y)');

real.ch3.coordinate = plot(Real.t(:),Real.z(:),'--ob','Visible','off','DisplayName', 'z');
real.ch3.speed = plot(Real.t(:),Real.Vz(:),'--ob','Visible','off','DisplayName', 'V(z)');
real.ch3.acceleration = plot(Real.t(:),Real.az(:),'--ob','Visible','off','DisplayName', 'a(z)');

legendOff();

assignin('base','realPlot',real);

function voiCheckboxAssignin(VOI)
voi.ch1.coordinate = plot(VOI.t(:),VOI.x(:),'-*g','Visible','off','DisplayName', 'x');
voi.ch1.speed = plot(VOI.t(:),VOI.Vx(:),'-*g','Visible','off','DisplayName', 'V(x)');
voi.ch1.acceleration = plot(VOI.t(:),VOI.ax(:),'-*g','Visible','off','DisplayName', 'a(x)');

voi.ch2.coordinate = plot(VOI.t(:),VOI.y(:),'-*r','Visible','off','DisplayName', 'y');
voi.ch2.speed = plot(VOI.t(:),VOI.Vy(:),'-*r','Visible','off','DisplayName', 'V(y)');
voi.ch2.acceleration = plot(VOI.t(:),VOI.ay(:),'-*r','Visible','off','DisplayName', 'a(y)');

voi.ch3.coordinate = plot(VOI.t(:),VOI.z(:),'-*b','Visible','off','DisplayName', 'z');
voi.ch3.speed = plot(VOI.t(:),VOI.Vz(:),'-*b','Visible','off','DisplayName', 'V(z)');
voi.ch3.acceleration = plot(VOI.t(:),VOI.az(:),'-*b','Visible','off','DisplayName', 'a(z)');

legendOff();

assignin('base','voiPlot',voi);

function poiCheckboxAssignin(POI)
poi.ch5.coordinate = plot(POI.t(:),POI.x(:),'-.g','Visible','off','DisplayName', 'ПОИ x');
poi.ch6.coordinate = plot(POI.t(:),POI.y(:),'-.r','Visible','off','DisplayName', 'ПОИ y');
poi.ch7.coordinate = plot(POI.t(:),POI.z(:),'-.b','Visible','off','DisplayName', 'ПОИ z');

assignin('base','poiPlot',poi);

function deletePOIPlot()
poi = evalin('base','poiPlot');
delete (poi.ch5.coordinate);
delete (poi.ch6.coordinate);
delete (poi.ch7.coordinate);

function noizeCheckboxAssignin(Noize)
noize.ch9.coordinate = plot(Noize.t(:),Noize.x(:),':g','Visible','off','DisplayName', 'Шумы по x');
noize.ch10.coordinate = plot(Noize.t(:),Noize.y(:),':r','Visible','off','DisplayName', 'Шумы по y');
noize.ch11.coordinate = plot(Noize.t(:),Noize.z(:),':b','Visible','off','DisplayName', 'Шумы по z');

assignin('base','noizePlot',noize);

function deleteNoizePlot()
noize = evalin('base','noizePlot');
delete (noize.ch9.coordinate);
delete (noize.ch10.coordinate);
delete (noize.ch11.coordinate);

% --- Отключение чекбоксов
function checkboxOff(handles)
    set(handles.checkbox1,'Value',0);
    set(handles.checkbox2,'Value',0);
    set(handles.checkbox3,'Value',0);
    
function checkboxPOIOff(handles)
    set(handles.checkbox5,'Value',0);
    set(handles.checkbox6,'Value',0);
    set(handles.checkbox7,'Value',0);
    
function checkboxNoizeOff(handles)
    set(handles.checkbox9,'Value',0);
    set(handles.checkbox10,'Value',0);
    set(handles.checkbox11,'Value',0);
    
% --- Именование чекбоксов по координатам
function checkboxCoordinateName(handles)
%     set(handles.checkbox1,'String','Координата X');
%     set(handles.checkbox2,'String','Координата Y');
%     set(handles.checkbox3,'String','Координата Z');
    ylabel('Координаты, m')
    
% --- Именование чекбоксов по скорости
function checkboxSpeedName(handles)
%     set(handles.checkbox1,'String','Скорость V(X)');
%     set(handles.checkbox2,'String','Скорость V(Y)');
%     set(handles.checkbox3,'String','Скорость V(Z)');
    ylabel('Скорость, m/s')
    
% --- Именование чекбоксов по ускорению
function checkboxAccelerateName(handles)
%     set(handles.checkbox1,'String','Ускорение a(X)');
%     set(handles.checkbox2,'String','Ускорение a(Y)');
%     set(handles.checkbox3,'String','Ускорение a(Z)');
    ylabel('Ускорение, m/s^2')
     
% --- Убираются все линии с графика
function linesOff()
    realPlot = evalin('base','realPlot');
    voiPlot = evalin('base','voiPlot');
    
    setLinesOff(realPlot);
    setLinesOff(voiPlot);

function setLinesOff(inform)
    set(inform.ch1.coordinate,'Visible','off');
    set(inform.ch1.speed,'Visible','off');
    set(inform.ch1.acceleration,'Visible','off');
    
    set(inform.ch2.coordinate,'Visible','off');
    set(inform.ch2.speed,'Visible','off');
    set(inform.ch2.acceleration,'Visible','off');
    
    set(inform.ch3.coordinate,'Visible','off');
    set(inform.ch3.speed,'Visible','off');
    set(inform.ch3.acceleration,'Visible','off');

function makeLegendAfterListbox(handles)
    realPlot = evalin('base','realPlot');
    voiPlot = evalin('base','voiPlot');
    contents = get(handles.popupmenu1, 'Value');
    switch contents
        case 1
            chPoi = get(handles.checkbox4,'Value');
            chNoize = get(handles.checkbox8,'Value');
            if(chPoi == 0 && chNoize == 0)
            legend([realPlot.ch1.coordinate,realPlot.ch2.coordinate,realPlot.ch3.coordinate,...
                voiPlot.ch1.coordinate,voiPlot.ch2.coordinate,voiPlot.ch3.coordinate,],...
                'Эталон x','Эталон y','Эталон z','ВОИ x','ВОИ y','ВОИ z');
            end
            if(chPoi == 1 && chNoize == 0)
                poiPlot = evalin('base','poiPlot');
                legend([realPlot.ch1.coordinate,realPlot.ch2.coordinate,realPlot.ch3.coordinate,...
                voiPlot.ch1.coordinate,voiPlot.ch2.coordinate,voiPlot.ch3.coordinate,...
                poiPlot.ch5.coordinate,poiPlot.ch6.coordinate,poiPlot.ch7.coordinate],...
                'Эталон x','Эталон y','Эталон z','ВОИ x','ВОИ y','ВОИ z','ПОИ x','ПОИ y','ПОИ z' );
            end
            if(chPoi == 0 && chNoize == 1)
                    noizePlot = evalin('base','noizePlot');
                legend([realPlot.ch1.coordinate,realPlot.ch2.coordinate,realPlot.ch3.coordinate,...
                voiPlot.ch1.coordinate,voiPlot.ch2.coordinate,voiPlot.ch3.coordinate,...
                noizePlot.ch9.coordinate,noizePlot.ch10.coordinate,noizePlot.ch11.coordinate],...
                'Эталон x','Эталон y','Эталон z','ВОИ x','ВОИ y','ВОИ z','Шумы по x','Шумы по y','Шумы по x');
            end
            if(chNoize == 1 && chPoi == 1)
                    noizePlot = evalin('base','noizePlot');
                poiPlot = evalin('base','poiPlot');
                legend([realPlot.ch1.coordinate,realPlot.ch2.coordinate,realPlot.ch3.coordinate,...
                voiPlot.ch1.coordinate,voiPlot.ch2.coordinate,voiPlot.ch3.coordinate,...
                poiPlot.ch5.coordinate,poiPlot.ch6.coordinate,poiPlot.ch7.coordinate,...
                noizePlot.ch9.coordinate,noizePlot.ch10.coordinate,noizePlot.ch11.coordinate],...
                'Эталон x','Эталон y','Эталон z','ВОИ x','ВОИ y','ВОИ z','ПОИ x','ПОИ y','ПОИ z',...
                'Шумы по x','Шумы по y','Шумы по x' );
            end
        case 2
            legend([realPlot.ch1.speed,realPlot.ch2.speed,realPlot.ch3.speed,...
                 voiPlot.ch1.speed,voiPlot.ch2.speed,voiPlot.ch3.speed,],...
                 'Эталон Vx','Эталон Vy','Эталон Vz','ВОИ Vx','ВОИ Vy','ВОИ Vz' );
        case 3
            legend([realPlot.ch1.acceleration,realPlot.ch2.acceleration,realPlot.ch3.acceleration,...
                voiPlot.ch1.acceleration,voiPlot.ch2.acceleration,voiPlot.ch3.acceleration,],...
                'Эталон ax','Эталон ay','Эталон az','ВОИ ax','ВОИ ay','ВОИ az' );     
    end
    
function legendOff()
    s = findobj('type','legend');
    delete(s);

function informationAssigning()
load 71118;
assignin('base','Real',Real);
assignin('base','VOI',VOI);
assignin('base','POI',POI)

function defaultSetting(handles)
% Настраиваем график
grid on;
hold on;
xlabel('Время, s');
ylabel('Координаты, m');

informationAssigning();
Real = evalin('base','Real');
VOI = evalin('base','VOI');

realCheckboxAssignin(Real(1))
voiCheckboxAssignin(VOI(1));

realPlot = evalin('base','realPlot');
voiPlot = evalin('base','voiPlot');

setListboxes(handles);

legend([realPlot.ch1.coordinate,realPlot.ch2.coordinate,realPlot.ch3.coordinate,...
    voiPlot.ch1.coordinate,voiPlot.ch2.coordinate,voiPlot.ch3.coordinate,],...
    'Эталон x','Эталон y','Эталон z','ВОИ x','ВОИ y','ВОИ z' );


function setListboxes(handles)
Real = evalin('base','Real');
VOI = evalin('base','VOI');

    linesOff();
    checkboxOff(handles);
    realSize = size(Real);
    set(handles.listbox1,'String', 'Эталонная цель 1');
    for i = 2:realSize(2)
        strPart = char("Эталонная цель " + i);
        oldStr = get(handles.listbox1,'String');
        newStr = char(oldStr, strPart);
        set(handles.listbox1,'String', newStr);
    end
    
    VoiSize = size(VOI);
    set(handles.listbox2,'String', 'ВОИ 1');
    for i = 2:VoiSize(2)
        strPart = char("ВОИ " + i);
        oldStr = get(handles.listbox2,'String');
        newStr = char(oldStr, strPart);
        set(handles.listbox2,'String', newStr);
    end
