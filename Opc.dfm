object OpcjeForm: TOpcjeForm
  Left = 378
  Top = 385
  BorderStyle = bsDialog
  Caption = 'Opcje'
  ClientHeight = 124
  ClientWidth = 244
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  PrintScale = poNone
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 2
    Width = 3
    Height = 13
  end
  object Edit2: TEdit
    Left = 8
    Top = 56
    Width = 89
    Height = 21
    TabOrder = 3
    Text = '0'
    OnKeyDown = Edit2KeyDown
  end
  object Edit3: TEdit
    Left = 8
    Top = 94
    Width = 89
    Height = 21
    TabOrder = 0
    Text = '0'
    OnKeyDown = Edit3KeyDown
  end
  object UpDown3: TUpDown
    Left = 97
    Top = 94
    Width = 15
    Height = 21
    Associate = Edit3
    Min = 0
    Max = 600
    Position = 0
    TabOrder = 1
    Wrap = False
  end
  object BitBtn1: TBitBtn
    Left = 120
    Top = 4
    Width = 117
    Height = 113
    Caption = 'OK'
    TabOrder = 2
  end
  object Edit1: TEdit
    Left = 8
    Top = 8
    Width = 89
    Height = 21
    TabOrder = 4
    Text = 'Edit1'
  end
  object UpDown1: TUpDown
    Left = 96
    Top = 8
    Width = 16
    Height = 24
    Min = 0
    Position = 0
    TabOrder = 5
    Wrap = False
  end
  object UpDown2: TUpDown
    Left = 96
    Top = 56
    Width = 16
    Height = 24
    Min = 0
    Position = 0
    TabOrder = 6
    Wrap = False
  end
end
