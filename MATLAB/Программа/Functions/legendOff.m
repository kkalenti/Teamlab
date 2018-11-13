% --- Удаляется легенда
function legendOff()
    s = findobj('type','legend');
    delete(s);
