<GameFile>
  <PropertyGroup Name="UIupdateResourceScene" Type="Scene" ID="40e435d6-b2bf-4d42-bf60-b5c19da22ed5" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Scene" Tag="6" ctype="GameNodeObjectData">
        <Size X="960.0000" Y="640.0000" />
        <Children>
          <AbstractNodeData Name="root" ActionTag="1492653076" Tag="19" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="480.0000" RightMargin="480.0000" TopMargin="320.0000" BottomMargin="320.0000" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="bg" ActionTag="-760759238" CallBackType="Touch" CallBackName="on_bug_switch_root" Tag="20" IconVisible="False" LeftMargin="-480.0000" RightMargin="-480.0000" TopMargin="-320.0000" BottomMargin="-320.0000" TouchEnable="True" LeftEage="316" RightEage="316" TopEage="211" BottomEage="211" Scale9OriginX="316" Scale9OriginY="211" Scale9Width="328" Scale9Height="218" ctype="ImageViewObjectData">
                <Size X="960.0000" Y="640.0000" />
                <Children>
                  <AbstractNodeData Name="logo" ActionTag="-127080428" Tag="23" IconVisible="False" LeftMargin="703.5236" RightMargin="0.4764" TopMargin="-0.2213" BottomMargin="500.2213" BottomEage="46" Scale9Width="544" Scale9Height="252" ctype="ImageViewObjectData">
                    <Size X="256.0000" Y="140.0000" />
                    <AnchorPoint ScaleX="1.0000" ScaleY="1.0000" />
                    <Position X="959.5236" Y="640.2213" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.9995" Y="1.0003" />
                    <PreSize X="0.2667" Y="0.2188" />
                    <FileData Type="Normal" Path="prveLoginLang/ch/iconlogo.png" Plist="" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="prveLogin/loadingBg.jpg" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="480.0000" Y="320.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="loadingLayer" ActionTag="-754438224" Tag="31" IconVisible="False" PositionPercentXEnabled="True" PercentWidthEnable="True" PercentWidthEnabled="True" TopMargin="570.0000" BottomMargin="10.0000" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" ctype="PanelObjectData">
            <Size X="960.0000" Y="60.0000" />
            <Children>
              <AbstractNodeData Name="speedState" ActionTag="-1481294184" Tag="26" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="304.5000" RightMargin="304.5000" TopMargin="42.0000" FontSize="18" LabelText="速度进度表下载进度(1302kb/240mb 300k/s)" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="351.0000" Y="18.0000" />
                <AnchorPoint ScaleX="0.5000" />
                <Position X="480.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="0" G="128" B="0" />
                <PrePosition X="0.5000" />
                <PreSize X="0.3656" Y="0.3000" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="loading" ActionTag="1627509470" CallBackName="onUpdateEvent" Tag="32" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="440.0000" RightMargin="440.0000" TopMargin="13.0000" BottomMargin="13.0000" TouchEnable="True" PercentInfo="100" DisplayState="False" ctype="SliderObjectData">
                <Size X="80.0000" Y="34.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="480.0000" Y="30.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="0.0833" Y="0.5667" />
                <ProgressBarData Type="Normal" Path="prveLogin/loadingFront.png" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" />
            <Position X="480.0000" Y="10.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.0156" />
            <PreSize X="1.0000" Y="0.0938" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="tipsTexts" ActionTag="-1153808208" Tag="33" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="210.0000" RightMargin="210.0000" TopMargin="552.9824" BottomMargin="72.0176" FontSize="15" LabelText="游戏中出现任何异常可以联系客服，如果不能到大厅，请在闪屏界面点击紧急反馈" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="540.0000" Y="15.0000" />
            <AnchorPoint ScaleX="0.5000" />
            <Position X="480.0000" Y="72.0176" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="0" B="0" />
            <PrePosition X="0.5000" Y="0.1125" />
            <PreSize X="0.5625" Y="0.0234" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>