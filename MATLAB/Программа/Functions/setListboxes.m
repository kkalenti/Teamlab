% --- Формируются списки целей, в зависимости от количества целей
function setListboxes(handles)
Real = evalin('base','Real');
VOI = evalin('base','VOI');
Hypo = evalin('base','Hypo');

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
    
    HypoSize = size(Hypo);
    set(handles.listbox3,'String', 'Гипотеза 1');
    for i = 2:HypoSize(2)
        strPart = char("Гипотеза " + i);
        oldStr = get(handles.listbox3,'String');
        newStr = char(oldStr, strPart);
        set(handles.listbox3,'String', newStr);
    end
