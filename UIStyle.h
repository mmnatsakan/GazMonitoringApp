#ifndef UISTYLE_H
#define UISTYLE_H

#include <QString>

const QString LABEL_STYLE_SHEET = "QLabel{ font-size: 14px; color: #000000; border: none;}";
const QString START_PAGE_LABEL_STYLE_SHEET = "QLabel{ font-size: 18px; color: #000000; font-weight: 600; border: none;}";

const QString LINE_EDIT_STYLE_SHEET =  "QLineEdit{padding: 5px 5px; font-size: 14px; font-weight: 400; color: red; background: #98FF98; border: 1px solid green; border-radius: 10px;}";

const QString PUSH_BUTTON_STYLE_SHEET = "QPushButton{border: none; outline: none; color: #000000; font-size: 18px; font-weight: 600; background: #87CEEB; border-radius: 5px; padding: 7px 20px;}"\
                                        "QPushButton:disabled{background: transparent; border: 1px solid #999ca6;}"\
                                        "QPushButton:hover{background: #02768C;}"\
                                        "QPushButton:pressed{background: #318394;}";

const QString ICON_PUSH_BUTTON_STYLE_SHEET =    "QPushButton{height: 40; weight: 40; border: none; outline: none; background: #87CEEB; border-radius: 5px;}"\
                                                "QPushButton:disabled{background: transparent; border: 1px solid #999ca6;}"\
                                                "QPushButton:hover{background: #02768C;}"\
                                                "QPushButton:pressed{background: #318394;}";

const QString SCROLLBAR_STYLE_SHEET =   "QScrollBar:vertical {border: none; border-radius: 8px; background: transparent; width: 30px; }"\
                                        "QScrollBar::handle:vertical {border: none; background: #808c9c; min-height: 10px; border-radius: 8px; }"\
                                        "QScrollBar::add-line:vertical { border: none; height: 0px; subcontrol-position: bottom; subcontrol-origin: margin; }"\
                                        "QScrollBar::sub-line:vertical { border: none; height: 0px; subcontrol-position: top; subcontrol-origin: margin; } "\
                                        "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical { border: none; background: transparent; } "\
                                        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: transparent; }";

// const QString RADIO_BUTTON_STYLE_SHEET = "QRadioButton::indicator{width: 15px; height: 15px;}"\
//                                         "QRadioButton::indicator::checked{image: url(':/icon_radiobutton_checked.svg');}"\
//                                         "QRadioButton::indicator::unchecked{image: url(':/icon_radiobutton_unchecked.svg');}"\
//                                         "QRadioButton{color: #000000; font-size: 14px; font-family: Arial;}";

const QString TABLE_WIDGET_STYLE_SHEET =    "QTableWidget, QTableWidget:disabled {gridline-color: gray; background-color: white; alternate-background-color: #f2f2f2; font-size: 14px; font-weight: 400}"\
                                            "QHeaderView::section {background-color: lightgray; padding: 5px; border: 1px solid gray; font-size: 14px; font-weight: 600;}"\
                                            "QTableWidget::item {border: 1px solid gray; padding: 5px;}";

const QString COMBOBOX_STYLE_SHEET =    "QComboBox {height: 18px; background-color: #ffffff; color: #000000; border-radius: 2px; font-size: 18px; font-weight: 600; padding-top: 10px; padding-bottom: 10px; padding-left: 5px;}"\
                                        "QComboBox:on{background-color: lightBlue;}"\
                                        "QAbstractItemView{border-radius: 2px; border: 1px solid gray; background-color: #FFFFFF;}"\
                                        "QAbstractItemView::item{ color: #000000; border-radius: 2px; background-color: transparent; margin: 5px;}"\
                                        "QAbstractItemView::item:hover{background-color: #dddddd}"\
                                        "QComboBox::item{border: none;}"\
                                        "QComboBox::drop-down {border: none; background: transparent;}"\
                                        "QComboBox::down-arrow{ image: url(':/icons/down_arrow_big.svg'); margin-right: 4px; margin-left: 2px}";

const QString TABLE_VIEW_STYLE_SHEET = "QTableView {background-color: rgb(255, 255, 255); alternate-background-color: rgb(200, 200, 200); border: none; gridline-color: rgb(231, 231, 231);"
                                       "font-size: 16px; color: rgb(0, 0, 0); }"
                                       "QTableView::item { background-color: transparent; }"
                                       "QTableView::item:selected { background-color: lightBlue; }"
                                       "QTableView::viewport { background-color: rgb(255, 255, 255); }"
                                       "QHeaderView { background: rgb(255, 255, 255); border: 1px solid rgb(231, 231, 231);}"
                                       "QHeaderView::section { text-align: center; min-width: 30px; min-height: 50px; border: 1px outset rgb(223, 223, 223);"
                                       " font-size: 16px; background-color: rgb(255, 255, 255); color: rgb(222, 109, 5); }";

const QString MEKNAB_CHECKBOX_STYLE_SHEET = "QCheckBox::indicator{width: 15px; height: 15px;}"\
                                            "QCheckBox{color: #000000; font-size: 14px;}";

const QString CHECKBOX_STYLE_SHEET =    "QCheckBox::indicator{width: 20px; height: 20px;}"\
                                        "QCheckBox{color: #000000; font-size: 18px;}";

const QString TEXTBOX_STYLE_SHEET = "QTextEdit{padding: 5px; font-size: 14px; font-weight: 400; color: black; background: white;"\
                                    " border: 1px solid #98FF98; border-radius: 10px;}";


#endif // UISTYLE_H
