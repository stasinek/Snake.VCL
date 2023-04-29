object MainForm: TMainForm
  Left = 257
  Top = 290
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'SNAKE 1.0'
  ClientHeight = 84
  ClientWidth = 435
  Color = clBlack
  Constraints.MinHeight = 130
  Constraints.MinWidth = 430
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWhite
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010002002020100000000000E80200002600000010101000000000002801
    00000E0300002800000020000000400000000100040000000000800200000000
    0000000000000000000000000000000000000000800000800000008080008000
    00008000800080800000C0C0C000808080000000FF0000FF000000FFFF00FF00
    0000FF00FF00FFFF0000FFFFFF00000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000009
    9999999999999999999999999000000999999999999999999999999990000009
    9999999999999999999999999000000999999999999999999999999990000000
    0000000000000000000009999000000000000000000000000000099990000000
    0000000000000000000009999000000000000000000000000000099990000009
    9999999999999999999999999000000999999999999999999999999990000009
    9999999999999999999999999000000999999999999999999999999990000009
    9990000000000000000000000000000999900000000000000000000000000009
    9990000000000000000000000000000999900000000000000000000000000009
    9990000000999999999999900000000999900000009999999999999000000009
    9990000000999999000000000000000999999999999999999999999000000009
    9999999999999999999999900000000999999999999990099999999000000009
    9999999999999009999999900000000000000000009999999999999000000000
    0000000000999999999999900000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000FFFFFFFFFFFFFFFFC0000003C0000003C000
    0003C0000003C0000003C0000003FFFFFF03FFFFFF03C0000003C0000003C000
    0003C0000003C0000003C0000003C0FFFFFFC0FFFFFFC0F8000FC0F8000FC0F8
    000FC000000FC000000FC000000FC000000FC000000FC000000FFFF8000FFFF8
    000FFFFFFFFFFFFFFFFFFFFFFFFF280000001000000020000000010004000000
    0000C00000000000000000000000000000000000000000000000000080000080
    000000808000800000008000800080800000C0C0C000808080000000FF0000FF
    000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0000000000000000000000
    0000000000000099999999999000000000000000900000000000000090000000
    0000000090000099999999999000009000000000100000900000000000000090
    0000000000000090000999999000009999999990000000000009099990000000
    00099999900000000000000000000000000000000000FFFF0000800300008003
    000080030000FFE300008003000080030000800300008FFF00008C0300008003
    00008003000080030000FC030000FC030000FFFF0000}
  Menu = MainMenu1
  OldCreateOrder = True
  PopupMenu = PopupMenu1
  Position = poScreenCenter
  PrintScale = poNone
  Scaled = False
  OnClose = FormClose
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnPaint = FormPaint
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 65
    Width = 435
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object PopupMenu1: TPopupMenu
    Left = 44
    Top = 4
    object Gra: TMenuItem
      Caption = 'G&ra'
      object Start: TMenuItem
        Caption = 'Sta&rt'
        Enabled = False
        OnClick = StartClick
      end
      object Stop: TMenuItem
        Caption = '&Stop'
        Enabled = False
        OnClick = StopClick
      end
      object Pauza: TMenuItem
        Caption = '&Pauza'
        Enabled = False
        OnClick = PauzaClick
      end
    end
    object Mapka: TMenuItem
      Caption = '&Mapa F1-F12'
      object N11: TMenuItem
        Caption = '1'
        Enabled = False
        ShortCut = 112
        Visible = False
        OnClick = N11Click
      end
      object N21: TMenuItem
        Caption = '2'
        Enabled = False
        ShortCut = 113
        Visible = False
        OnClick = N21Click
      end
      object N31: TMenuItem
        Caption = '3'
        Enabled = False
        ShortCut = 114
        Visible = False
        OnClick = N31Click
      end
      object N41: TMenuItem
        Caption = '4'
        Enabled = False
        ShortCut = 115
        Visible = False
        OnClick = N41Click
      end
      object N51: TMenuItem
        Caption = '5'
        Enabled = False
        ShortCut = 116
        Visible = False
        OnClick = N51Click
      end
      object N61: TMenuItem
        Caption = '6'
        Enabled = False
        ShortCut = 117
        Visible = False
        OnClick = N61Click
      end
      object N71: TMenuItem
        Caption = '7'
        Enabled = False
        ShortCut = 118
        Visible = False
        OnClick = N71Click
      end
      object N81: TMenuItem
        Caption = '8'
        Enabled = False
        ShortCut = 119
        Visible = False
        OnClick = N81Click
      end
      object N91: TMenuItem
        Caption = '9'
        Enabled = False
        ShortCut = 120
        Visible = False
        OnClick = N91Click
      end
      object N101: TMenuItem
        Caption = '10'
        Enabled = False
        ShortCut = 121
        Visible = False
        OnClick = N101Click
      end
      object N111: TMenuItem
        Caption = '11'
        Enabled = False
        ShortCut = 122
        Visible = False
        OnClick = N111Click
      end
      object N121: TMenuItem
        Caption = '12'
        Enabled = False
        ShortCut = 123
        Visible = False
        OnClick = N121Click
      end
    end
    object Opcje: TMenuItem
      Caption = '&Opcje gry'
      OnClick = OpcjeClick
    end
    object About: TMenuItem
      Caption = '&O...'
      OnClick = AboutClick
    end
    object Zamknij: TMenuItem
      Caption = '&Koniec'
      OnClick = ZamknijClick
    end
  end
  object MainMenu1: TMainMenu
    Left = 112
    Top = 4
    object Start2: TMenuItem
      Caption = 'Sta&rt'
      Enabled = False
      OnClick = StartClick
    end
    object Pauza2: TMenuItem
      Caption = '&Pauza'
      Enabled = False
      OnClick = PauzaClick
    end
    object Stop2: TMenuItem
      Caption = '&Stop'
      Enabled = False
      OnClick = StopClick
    end
    object N2: TMenuItem
      Caption = '|'
    end
    object Mapka2: TMenuItem
      Caption = '&Mapa F1-F12'
      OnClick = Mapka2Click
    end
    object Opcje2: TMenuItem
      Caption = '&Opcje'
      OnClick = OpcjeClick
    end
    object N1: TMenuItem
      Caption = '|'
    end
    object About2: TMenuItem
      Caption = '&O...'
      OnClick = AboutClick
    end
    object Zamknij2: TMenuItem
      Caption = '&KONIEC'
      OnClick = ZamknijClick
    end
  end
end
