#ifndef UISTYLE_H
#define UISTYLE_H

#include <QString>

const QString LABEL_STYLE_SHEET = "QLabel{ font-size: 14px; color: #000000; border: none;}";

const QString LINE_EDIT_STYLE_SHEET =  "QLineEdit{padding: 5px 5px; font-size: 14px; font-weight: 400; font-family: Arial; color: red; background: #98FF98; border: 1px solid green; border-radius: 10px;}";

const QString PUSH_BUTTON_STYLE_SHEET = "QPushButton{border: none; outline: none; color: #000000; font-size: 14px;  font-family: Arial; font-weight: 600; background: #87CEEB; border-radius: 5px; padding: 7px 20px;}"\
                                        "QPushButton:disabled{background: transparent; border: 1px solid #999ca6;}"\
                                        "QPushButton:hover{background: #02768C;}"\
                                        "QPushButton:pressed{background: #318394;}";

const QString SCROLLBAR_STYLE_SHEET =   "QScrollBar:vertical {border: none; border-radius: 8px; background: transparent; width: 16px; }"\
                                        "QScrollBar::handle:vertical {border: none; background: #808c9c; min-height: 10px; border-radius: 8px; }"\
                                        "QScrollBar::add-line:vertical { border: none; height: 0px; subcontrol-position: bottom; subcontrol-origin: margin; }"\
                                        "QScrollBar::sub-line:vertical { border: none; height: 0px; subcontrol-position: top; subcontrol-origin: margin; } "\
                                        "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical { border: none; background: transparent; } "\
                                        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: transparent; }";

const QString RADIO_BUTTON_STYLE_SHEET = "QRadioButton::indicator{width: 15px; height: 15px;}"\
                                        "QRadioButton::indicator::checked{image: url(':/icon_radiobutton_checked.svg');}"\
                                        "QRadioButton::indicator::unchecked{image: url(':/icon_radiobutton_unchecked.svg');}"\
                                        "QRadioButton{color: #000000; font-size: 14px; font-family: Arial;}";

const QString TABLE_WIDGET_STYLE_SHEET =    "QTableWidget, QTableWidget:disabled {gridline-color: black; background-color: white; alternate-background-color: #f2f2f2; font-size: 14px; font-weight: 400}"\
                                            "QHeaderView::section {background-color: lightgray; padding: 5px; border: 1px solid black; font-size: 14px; font-weight: 600;}"\
                                            "QTableWidget::item {border: 1px solid black; padding: 5px;}";

#endif // UISTYLE_H
