object Form1: TForm1
  Left = 314
  Top = 428
  Width = 430
  Height = 300
  Anchors = [akLeft, akTop, akRight, akBottom]
  Caption = 'Snake: MAPA'
  Color = clBtnFace
  Constraints.MinHeight = 300
  Constraints.MinWidth = 430
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 188
    Top = 8
    Width = 218
    Height = 178
    Anchors = [akTop, akRight, akBottom]
  end
  object Image1: TImage
    Left = 189
    Top = 9
    Width = 216
    Height = 176
    Anchors = [akTop, akRight, akBottom]
  end
  object ListBox1: TListBox
    Left = 12
    Top = 8
    Width = 161
    Height = 249
    Anchors = [akLeft, akTop, akRight, akBottom]
    ItemHeight = 13
    TabOrder = 0
    OnDblClick = ListBox1DblClick
  end
  object Button1: TButton
    Left = 300
    Top = 208
    Width = 107
    Height = 49
    Anchors = [akRight, akBottom]
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 1
    OnClick = ListBox1DblClick
  end
  object Button2: TButton
    Left = 188
    Top = 208
    Width = 97
    Height = 49
    Anchors = [akRight, akBottom]
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
    OnClick = Button2Click
  end
end
