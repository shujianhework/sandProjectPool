if App == nil then
	return
end
local Tlang = App:getData("langTab")
local lang = App:getData("lang")
if lang == nil then
	return
end	Tlang["ABOUTUS"] = [[關於我們]]
	Tlang["ACTIVE_DANBIYUAN_DES"] = [[活動期間,玩家單筆充值達到指定金額,即可獲得禮包一份。每檔獎勵只能領取一次哦!詳情見活動中心]]
	Tlang["ACTIVE_DANBIYUAN_INTRO"] = [[單筆充值%d<image>ui/icon/diamond.png</image>可獲得]]
	Tlang["ACTIVE_DANBIYUAN_TITLE"] = [[單筆充值]]
	Tlang["ACTIVE_DUIHUANMA_DES"] = [[大量回收兌換碼,我用好東西和你換哦!]]
	Tlang["ACTIVE_LEIJITIAN_DES"] = [[活動期間,玩家每天充值任意金額,即可在活動中心領取大禮一份,天天都有好禮可拿。累充天數越多,獎勵越豐厚!詳情見活動中心]]
	Tlang["ACTIVE_LEIJITIAN_INTRO"] = [[累積充值%d天可獲得(%d/%d)]]
	Tlang["ACTIVE_LEIJITIAN_TITLE"] = [[積天返利]]
	Tlang["ACTIVE_LEIJIXIAOGZUAN_DES"] = [[活動期間,玩家累積消費鑽石達到指定數目,即可獲得禮包一份。每檔獎勵只能領取一次哦!詳情見活動中心]]
	Tlang["ACTIVE_LEIJIXIAOGZUAN_INTRO"] = [[累積消費%d<image>ui/icon/diamond.png</image>可獲得(%d/%d)]]
	Tlang["ACTIVE_LEIJIXIAOZUAN_TITLE"] = [[累積消費]]
	Tlang["ACTIVE_LEIJIYUAN_DES"] = [[活動期間,玩家累計充值鑽石達到指定數目,即可獲得禮包一份。每檔獎勵只能領取一次哦!詳情見活動中心]]
	Tlang["ACTIVE_LEIJIYUAN_INTRO"] = [[累積充值%d<image>ui/icon/diamond.png</image>可獲得(%d/%d)]]
	Tlang["ACTIVE_LEIJIYUAN_TITLE"] = [[累積充值]]
	Tlang["ACTIVE_OPEN_FOREVER"] = [[永久開啟]]
	Tlang["ACTIVE_QIANDAO_DES"] = [[每天簽到均可獲得一份簽到獎勵,不要錯過哦!]]
	Tlang["ACTIVE_QIRIDENGLU_DES"] = [[活動期間登錄送好禮哦!]]
	Tlang["ACTIVE_TILI_DES"] = [[缺活力了嗎?只要在指定時間來這裏就可以領取活力哦]]
	Tlang["ACTIVE_TIME"] = [[活動時間]]
	Tlang["ACTUAL_TIME"] = [[匹配時間]]
	Tlang["ALI_LOGIN"] = [[支付寶登陸]]
	Tlang["ALI_LOGIN_TIPS"] = [[必須要安裝支付寶客戶端才可以登錄噢]]
	Tlang["ALL_SEVER"] = [[所有伺服器]]
	Tlang["ALREADY_FIGHT"] = [[被邀請的玩家已經在戰鬥]]
	Tlang["ARENA_SCORE"] = [[勝點]]
	Tlang["AUOTO_CANCEL"] = [[%s自動取消]]
	Tlang["BACK"] = [[返回]]
	Tlang["BACKTO_LOGIN"] = [[返回登錄]]
	Tlang["BISAIGUIZE"] = [[比賽規則]]
	Tlang["BLOCK"] = [[遮罩]]
	Tlang["BLOCK_CANCEL"] = [[取消遮罩]]
	Tlang["BLOCK_COMFIRM"] = [[是否遮罩此玩家的發言]]
	Tlang["BOSS_DE_1"] = [[因你在世界BOSS戰鬥中的英勇戰鬥,成功擊退敵人,特給予以下獎勵]]
	Tlang["BOSS_DE_2"] = [[本次世界BOSS活動結束,對BOSS造成最後一擊的是<style color:#fbe4ba>%s</style>,造成傷害最高的是<style color:#fbe4ba>%s</style>]]
	Tlang["BOSS_K_1"] = [[因你在世界BOSS戰鬥中的英勇戰鬥,成功擊斃BOSS,特給予以下獎勵]]
	Tlang["BOSS_NUM"] = [[剩餘購買次數]]
	Tlang["BOSS_P_1"] = [[感謝你參與世界BOSS戰鬥,保衛家園,獲得以下獎勵]]
	Tlang["BOSS_TIPS"] = [[世界BOSS已死亡]]
	Tlang["BREAKTHROUGH_MATERIAL"] = [[突破材料不足]]
	Tlang["BUILD_TEAM"] = [[創建隊伍]]
	Tlang["BUKELINGQU"] = [[領取]]
	Tlang["BUY_POWER_TIPS"] = [[體力已達上限,不能購買]]
	Tlang["CANCEL_MATCH"] = [[取消匹配]]
	Tlang["CANNOT_ENTER"] = [[不能重複進入本關卡]]
	Tlang["CANNOT_OBTAIN"] = [[請在規定時間領取]]
	Tlang["CHANGE"] = [[變化]]
	Tlang["CHANGE_BUTTON"] = [[更名]]
	Tlang["CHANGE_NAME"] = [[更換名稱]]
	Tlang["CHANGE_NAME_FAIL"] = [[更名失敗]]
	Tlang["CHANGE_NAME_SUCCES"] = [[更名成功]]
	Tlang["CHARGE_TIPS_1"] = [[商品錯誤!]]
	Tlang["CHARGE_TIPS_2"] = [[未能獲取商品資訊,請稍候再試!]]
	Tlang["CHARGE_TIPS_3"] = [[正在進行充值,請等待...]]
	Tlang["CHARGE_TIPS_4"] = [[我們未能驗證您的充值,請確保您的網路通暢!]]
	Tlang["CHARGE_TIPS_5"] = [[驗證充值失敗]]
	Tlang["CHARGE_TIPS_6"] = [[伺服器爆滿,請選擇其他伺服器]]
	Tlang["CHARGE_TIPS_7"] = [[遊戲有重大更新,請下載最新版遊戲]]
	Tlang["CHARGE_TIPS_8"] = [[下載成功,開始解壓資源包...]]
	Tlang["CHARGE_TIPS_9"] = [[解壓資源失敗,請檢查存儲空間是否足夠]]
	Tlang["CHECK_UPDATE"] = [[檢查更新]]
	Tlang["CHONGZHI"] = [[充值]]
	Tlang["CHONGZHICHENGGONG"] = [[充值成功]]
	Tlang["CHONGZHISHIBAI"] = [[充值失敗]]
	Tlang["CHOOSE_OTHER_SERVERS"] = [[選擇其他伺服器]]
	Tlang["COMPANY_INFO"] = [[遊戲中文名稱:百戰鬥鬥堂
應用類型:休閒競技
公司名稱:深圳市拇指遊玩科技有限公司
著作權人:成都千行科技有限公司
登記號:2016SR005635
審批文號:新廣出審【2016】3766號
出版單位:天津電子出版社有限公司
出版物號:ISBN 978-7-7979-2336-1
備案文號:文網遊備字〔2017〕Ｍ-SNG 0007 號]]
	Tlang["COMPANY_TIPS"] = [[遊戲著作權人:成都千行科技有限公司


出版服務單位:天津電子出版社有限公司


批准文號:新廣出審【2016】3766號


出版物號:ISBN978-7-7979-2336-1]]
	Tlang["CONDITION"] = [[通關條件]]
	Tlang["CONFIRM"] = [[確定]]
	Tlang["CONNECT_ERROR_1"] = [[您的網路異常,請切換至穩定的網路。]]
	Tlang["CREATE"] = [[創建]]
	Tlang["CURRENT_SERVER"] = [[當前分區]]
	Tlang["DAFA1"] = [[20度打法]]
	Tlang["DAFA10"] = [[高拋打法]]
	Tlang["DAFA2"] = [[45度打法]]
	Tlang["DAFA3"] = [[65度打法]]
	Tlang["DAFA4"] = [[注:距離可以通過右上角小地圖中標尺來測量]]
	Tlang["DAFA5"] = [[角度=90度-距離+風力(風力順風為正數,逆風為負數),力度為95]]
	Tlang["DAFA6"] = [[此打法,10距離以下,受風力影響較小,可忽略]]
	Tlang["DAFA7"] = [[此打法,較受風力影響一般]]
	Tlang["DAFA8"] = [[此打法,受風力影響很大,力度不變:角度:65+風力(風力順風為正數,逆風為負數)]]
	Tlang["DAFA9"] = [[競技打法]]
	Tlang["DATA_UNZIP"] = [[正在解壓]]
	Tlang["DENGLUJIANGLI"] = [[登錄驚喜]]
	Tlang["DESCRIPTION"] = [[描述]]
	Tlang["DOWNLOADING"] = [[加載資源中……]]
	Tlang["EASY"] = [[簡單]]
	Tlang["EASY_MANY"] = [[簡單]]
	Tlang["EFFECT"] = [[音效]]
	Tlang["ENTER_GAME"] = [[進入遊戲]]
	Tlang["ESTIMATED_TIME"] = [[預計時間]]
	Tlang["EVERYDAY"] = [[每天]]
	Tlang["EWAIZENGSONG"] = [[額外贈送%d <image>ui/icon/diamond.png</image>]]
	Tlang["EXIT_BATTLE"] = [[退出戰鬥]]
	Tlang["FANHUIDENGLU"] = [[親,網路中斷了,請重新登錄]]
	Tlang["FAST_REGIST"] = [[快速註冊]]
	Tlang["FIGHT_TIMES"] = [[戰鬥次數]]
	Tlang["FIRST_FREE"] = [[首次更名免費]]
	Tlang["FRIDAY"] = [[星期五]]
	Tlang["FUBENJIESHAO"] = [[副本介紹]]
	Tlang["FUWENSHENGDI"] = [[符文聖地]]
	Tlang["FUWUTIAOKUAN"] = [[一,特別提示

  在此特別提醒您(用戶)在註冊成為百戰鬥鬥堂用戶之前,請認真閱讀本《百戰鬥鬥堂用戶服務協議》(以下簡稱"協議"),確保您充分理解本協議中各條款。請您審慎閱讀並選擇接受或不接受本協議。除非您接受本協議所有條款,否則您無權註冊,登錄或使用本協議所涉服務。您的註冊,登錄,使用等行為將視為對本協議的接受,並同意接受本協議各項條款的約束。
  本協議約定百戰鬥鬥堂與用戶之間關於"百戰鬥鬥堂用戶"服務(以下簡稱"服務")的權利義務。"用戶"是指註冊,登錄,使用本服務的個人。本協議可由百戰鬥鬥堂隨時更新,更新後的協議條款一旦公佈即代替原來的協議條款,恕不再另行通知,用戶可在本APP中查閱最新版協議條款。在修改協議條款後,如果用戶不接受修改後的條款,請立即停止使用百戰鬥鬥堂提供的服務,用戶繼續使用百戰鬥鬥堂提供的服務將被視為接受修改後的協議。

二,用戶聲明與保證

  1,用戶承諾其為具有完全民事行為能力的民事主體,且具有達成交易履行其義務的能力。
  2,用戶有義務在註冊時提供自己的真實資料,並保證諸如手機號碼,姓名,所在地區等內容的有效性及安全性,保證百戰鬥鬥堂工作人員可以通過上述聯繫方式與用戶取得聯繫。同時,用戶也有義務在相關資料實際變更時及時更新有關註冊資料。
  3,用戶通過使用百戰鬥鬥堂的過程中所製作,上載,複製,發佈,傳播的任何內容,包括但不限於帳號頭像,名稱,用戶說明等註冊資訊及認證資料,或文字,語音,圖片,視頻,圖文等發送,回復和相關鏈接頁面,以及其他使用帳號或本服務所產生的內容,不得違反國家相關法律制度,包含但不限於如下原則:
  (1)反對憲法所確定的基本原則的:
  (2)危害國家安全,洩露國家秘密,顛覆國家政權,破壞國家統一的:
  (3)損害國家榮譽和利益的:
  (4)煽動民族仇恨,民族歧視,破壞民族團結的:
  (5)破壞國家宗教政策,宣揚邪教和封建迷信的:
  (6)散佈謠言,擾亂社會秩序,破壞社會穩定的:
  (7)散佈淫穢,色情,賭博,暴力,兇殺,恐怖或者教唆犯罪的:
  (8)侮辱或者誹謗他人,侵害他人合法權益的:
  (9)含有法律,行政法規禁止的其他內容的。
  4,用戶不得利用"百戰鬥鬥堂"帳號或本服務制作,上載,複製,發佈,傳播下干擾"百戰鬥鬥堂"正常運營,以及侵犯其他用戶或第三方合法權益的內容:
  (1)含有任何性或性暗示的:
  (2)含有辱罵,恐嚇,威脅內容的:
  (3)含有騷擾,垃圾廣告,惡意資訊,誘騙資訊的:
  (4)涉及他人隱私,個人資訊或資料的:
  (5)侵害他人名譽權,肖像權,知識產權,商業秘密等合法權利的:
  (6)含有其他干擾本服務正常運營和侵犯其他用戶或第三方合法權益內容的資訊。

三,服務內容

  1,具體服務內容由百戰鬥鬥堂根據實際情況提供,包括但不限於:
  (1)線上諮詢服務:
  (2)服務商收入結算和用戶支付費用:具體金額以產生的統計數據為准。
  2,百戰鬥鬥堂有權隨時審核或刪除用戶發佈/傳播的涉嫌違法或違反社會主義精神文明,或者被百戰鬥鬥堂認為不妥當的內容(包括但不限於文字,語音,圖片,視頻,圖文等)。
  3,所有發給用戶的通告及其他消息都可通過APP或者用戶所提供的聯繫方式發送。

四,服務的終止

  1,在下列情況下,百戰鬥鬥堂有權終止向用戶提供服務:
  (1)在用戶違反本服務協議相關規定時,百戰鬥鬥堂有權終止向該用戶提供服務。如該用戶再一次直接或間接或以他人名義註冊為用戶的,一經發現,百戰鬥鬥堂有權直接單方面終止向該用戶提供服務:
  (2)如百戰鬥鬥堂通過用戶提供的資訊與用戶聯繫時,發現用戶在註冊時填寫的聯繫方式已不存在或無法接通,百戰鬥鬥堂以其他聯繫方式通知用戶更改,而用戶在三個工作日內仍未能提供新的聯繫方式,百戰鬥鬥堂有權終止向該用戶提供服務:
  (3)用戶不得通過程式或人工方式進行刷量或作弊,若發現用戶有作弊行為,百戰鬥鬥堂將立即終止服務,並有權扣留帳戶內金額:
  (4)一旦百戰鬥鬥堂發現用戶提供的數據或資訊中含有虛假內容,百戰鬥鬥堂有權隨時終止向該用戶提供服務:
  (5)本服務條款終止或更新時,用戶明示不願接受新的服務條款:
  (6)其他百戰鬥鬥堂認為需終止服務的情況。
  2,服務終止後,百戰鬥鬥堂沒有義務為用戶保留原帳號中或與之相關的任何資訊,或轉發任何未曾閱讀或發送的資訊給用戶或第三方。

五,服務的變更,中斷

  1,鑒於網路服務的特殊性,用戶需同意百戰鬥鬥堂會變更,中斷部分或全部的網路服務,並刪除(不再保存)用戶在使用過程中提交的任何資料,而無需通知用戶,也無需對任何用戶或任何第三方承擔任何責任。
  2,百戰鬥鬥堂需要定期或不定期地對提供網路服務的平臺進行檢測或者更新,如因此類情況而造成網路服務在合理時間內的中斷,百戰鬥鬥堂無需為此承擔任何責任。

六,服務條款修改

  1,百戰鬥鬥堂有權隨時修改本服務條款的任何內容,一旦本服務條款的任何內容發生變動,百戰鬥鬥堂將會通過適當方式向用戶提示修改內容。
  2,如果不同意百戰鬥鬥堂對本服務條款所做的修改,用戶有權停止使用網路服務。
  3,如果用戶繼續使用網路服務,則視為用戶接受百戰鬥鬥堂對本服務條款所做的修改。

七,免責與賠償聲明

  1,若百戰鬥鬥堂已經明示其服務提供方式發生變更並提醒用戶應當注意事項,用戶未按要求操作所產生的一切後果由用戶自行承擔。
  2,用戶明確同意其使用百戰鬥鬥堂所存在的風險將完全由其自己承擔,因其使用百戰鬥鬥堂而產生的一切後果也由其自己承擔。
  3,用戶同意保障和維護百戰鬥鬥堂及其他用戶的利益,由於用戶在使用百戰鬥鬥堂有違法,不真實,不正當,侵犯第三方合法權益的行為,或用戶違反本協議項下的任何條款而給百戰鬥鬥堂及任何其他第三方造成損失,用戶同意承擔由此造成的損害賠償責任。

八,隱私聲明

  1,適用範圍:
  (1)在用戶註冊百戰鬥鬥堂帳戶時,根據要求提供的個人註冊資訊:
  (2)在用戶使用百戰鬥鬥堂,或訪問其相關網頁時,百戰鬥鬥堂自動接收並記錄的用戶流覽器上的伺服器數值,包括但不限於IP地址等數據及用戶要求取用的網頁記錄。
  2,資訊使用:
  (1)百戰鬥鬥堂不會向任何人出售或出借用戶的個人資訊,除非事先得到用戶的許可。
  (2)百戰鬥鬥堂亦不允許任何第三方以任何手段收集,編輯,出售或者無償傳播用戶的個人資訊。任何用戶如從事上述活動,一經發現,百戰鬥鬥堂有權立即終止與該用戶的服務協議,查封其帳號。
  (3)為達到服務用戶的目的,百戰鬥鬥堂可能通過使用用戶的個人資訊,向用戶提供服務,包括但不限於向用戶發出產品和服務資訊,或者與百戰鬥鬥堂合作夥伴共用資訊以便他們向用戶發送有關其產品和服務的資訊。
  3,資訊披露:用戶的個人資訊將在下述情況下部分或全部被披露:
  (1)經用戶同意,向第三方披露:
  (2)根據法律的有關規定,或者行政或司法機構的要求,向第三方或者行政,司法機構披露:
  (3)如果用戶出現違反中國有關法律或者網站政策的情況,需要向第三方披露:
  (4)為提供用戶所要求的產品和服務,而必須和第三方分享用戶的個人資訊:
  (5)其他百戰鬥鬥堂根據法律或者網站政策認為合適的披露:
  (6)用戶使用百戰鬥鬥堂時提供的銀行帳戶資訊,百戰鬥鬥堂將嚴格履行相關保密約定。

九,其他

  1,百戰鬥鬥堂鄭重提醒用戶注意本協議中免除責任和限制用戶權利的條款,請用戶仔細閱讀,自主考慮風險。未成年人應在法定監護人的陪同下閱讀本協議。
  2,本協議的效力,解釋及糾紛的解決,適用於中華人民共和國法律。若用戶和百戰鬥鬥堂之間發生任何糾紛或爭議,首先應友好協商解決,協商不成的,用戶同意將糾紛或爭議提交遊戲公司所地有管轄權的人民法院管轄。
  3,本協議的任何條款無論因何種原因無效或不具可執行性,其餘條款仍有效,對雙方具有約束力。
  4,本協議最終解釋權歸成都千行科技有限公司(簡稱"千行")所有,並且保留一切解釋和修改的權力。]]
	Tlang["GIFT"] = [[禮包]]
	Tlang["GO"] = [[開始]]
	Tlang["GOODS"] = [[物品]]
	Tlang["GUEST_LOGIN"] = [[遊客登錄]]
	Tlang["GUEST_LOGIN_WARN"] = [[敬愛的玩家,您正在使用遊客模式登錄遊戲,遊客模式下的遊戲數據(包含付費資訊)會在更換設備,清除緩存,卸載遊戲等操作之後清空。為了保障您的虛擬財產安全,以及讓您獲得更好的遊戲體驗,我們建議您使用支付寶帳號登錄。]]
	Tlang["GUILD_1"] = [[彈劾條件不滿足]]
	Tlang["GUILD_PROMPT"] = [[該公會在爭霸賽中,不能加入公會]]
	Tlang["HARD"] = [[困難]]
	Tlang["HARD_MANY"] = [[困難]]
	Tlang["HARM"] = [[傷害]]
	Tlang["HEISHITIPS"] = [[嘿,我這裏有各種寶貝,快來看看吧!]]
	Tlang["HIT_RATE"] = [[命中率]]
	Tlang["HONOR"] = [[榮譽]]
	Tlang["HOUSE_BUBBLE_TXT_1"] = [[天梯賽正在火熱進行中,快來贏取鑽石和榮譽吧!]]
	Tlang["HOUSE_BUBBLE_TXT_2"] = [[你還有符文沒有探索,趕快來探索吧!]]
	Tlang["HOUSE_BUBBLE_TXT_3"] = [[你有未收穫的符文,快來收穫吧!]]
	Tlang["HOUSE_BUBBLE_TXT_4"] = [[有新的寶物上架了,快來看看!]]
	Tlang["HUNLIDIANTANG"] = [[婚禮殿堂]]
	Tlang["INSTALL_TIP_1"] = [[接受隊伍邀請]]
	Tlang["INSTALL_TIP_3"] = [[自動接受好友邀請]]
	Tlang["INSTALL_TIP_4"] = [[不允許加為好友]]
	Tlang["INSTANCEBOUGHT_END"] = [[今日購買副本次數已經用完!]]
	Tlang["INSTANC_BUY_TITLE"] = [[購買次數]]
	Tlang["INVITE_PLAYER"] = [[邀請]]
	Tlang["INVITE_ROOM"] = [[<style color:#5bd600>%s</style> 邀請您進入房間,是否加入?]]
	Tlang["JINGCAIHUODONG"] = [[精彩活動]]
	Tlang["JINGJICHANG"] = [[競技場]]
	Tlang["JINGJICHANGTIPS"] = [[競技場正在火熱進行中,趕快來參加吧!]]
	Tlang["JINGXINGZHONG"] = [[已開啟]]
	Tlang["JITIAN"] = [[第%d天登錄]]
	Tlang["JULI"] = [[距離]]
	Tlang["KELINGQU"] = [[領取]]
	Tlang["KILL"] = [[擊殺]]
	Tlang["LADDER"] = [[個人天梯模式]]
	Tlang["LANGUAGE"] = [[語言]]
	Tlang["LEADDER_OPEN"] = [[等級達到%d級才能參加天梯賽]]
	Tlang["LEFT_TIME"] = [[剩餘次數:%d/%d]]
	Tlang["LEIJICISHU"] = [[本月已累積簽到%d次]]
	Tlang["LEIJIDENGLU"] = [[天天簽到]]
	Tlang["LIDU"] = [[力度]]
	Tlang["LINGZENG"] = [[另贈 %d <image>ui/icon/honor.png</image>]]
	Tlang["LOGIN"] = [[登錄]]
	Tlang["LOGIN_ANNONCE"] = [[公告]]
	Tlang["LOGIN_BAN"] = [[該角色被禁止登陸遊戲%s,詳情請聯繫客服]]
	Tlang["LOGIN_CONNECTING"] = [[正在進入鬥彈大陸……]]
	Tlang["LOGIN_INPUT_SPECIAL"] = [[抱歉,您的遊戲名字中包含部分暫不支持的特殊字元,請重新輸入]]
	Tlang["LOGIN_NOUPDATE"] = [[已是最新版本]]
	Tlang["LOGIN_TEXT_1"] = [[連續登陸%s天]]
	Tlang["LOGIN_TEXT_2"] = [[其他登錄]]
	Tlang["LOGIN_TEXT_3"] = [[帳號登錄]]
	Tlang["LOGIN_TEXT_4"] = [[QQ登錄]]
	Tlang["LOGIN_TEXT_5"] = [[微信登錄]]
	Tlang["LOGIN_TIPS"] = [[抵制不良遊戲,拒絕盜版遊戲。注意自我保護,謹防受騙上當。
適度遊戲益腦,沉迷遊戲傷身。合理安排時間,享受健康生活。]]
	Tlang["LOGIN_TIPS2"] = [[您的帳號已在其他設備上登錄]]
	Tlang["MAIN_FIRSTCHARGE_EXTRO"] = [[還可獲得珍貴物品:]]
	Tlang["MAIN_FIRSTCHARGE_GET"] = [[去充值]]
	Tlang["MAIN_FIRSTCHARGE_INTRO"] = [[首充<image>any_money.png</image>,]]
	Tlang["MAIN_FIRSTCHARGE_INTRO2"] = [[即可晉升為<image>vip_shangsi.png</image>,開啟<image>sweep.png</image>]]
	Tlang["MAIN_FIRSTCHARGE_TITLE"] = [[首充獎勵]]
	Tlang["MAIN_ONLINE_TITILE"] = [[線上獎勵]]
	Tlang["MALL"] = [[商城]]
	Tlang["MATCH_FAILED"] = [[匹配失敗]]
	Tlang["MATCH_WON"] = [[勝場]]
	Tlang["MATOUTIPS"] = [[遠征起航了,趕快來參加吧!]]
	Tlang["MAYBE_OBTAIN"] = [[可能獲得]]
	Tlang["MIAN_ONLINE_NEXT"] = [[距離下一次領獎還有]]
	Tlang["MODE_1"] = [[自由競技]]
	Tlang["MODE_10"] = [[死亡秘境]]
	Tlang["MODE_12"] = [[未開放]]
	Tlang["MODE_1_DES"] = [[1. 6級前僅可進行1V1的模式,6級後可自由選擇任意模式。
2. 自由競技將由系統為您匹配旗鼓相當的對手。
3. 在自由競技中可獲得榮譽,積累榮譽可以提升軍銜。
4. 在自由競技中獲得勝利,還可以為公會增加的活躍度哦。
5. 參加自由競技有幾率獲得武器和武器碎片。]]
	Tlang["MODE_2"] = [[天梯1V1
 排位賽]]
	Tlang["MODE_2_DES"] = [[1. 等級達到15級玩家即可參與天梯爭霸賽。
2. 通過5場定位賽決定您的初始天梯段位。
3. 天梯段位共分為青銅,白銀,黃金,鉑金,鑽石,王者6個段位,每個段位又分為"1","2","3","4","5"個等級。
4. 當您的勝點超過100則晉級:反之,段位勝點為0時,則降級。
5. 王者1段位中勝點超過100且排名前5的玩家,每日22:00段位結算後,可進入專屬段位---"鬥王"。
6. 每日可以領取3個天梯寶箱,分別需要:完成5場天梯賽,完成10場天梯賽,勝利5場天梯賽。
7. 天梯匹配系統將根據您的段位,在全服尋找與您段位接近的對手。
8. 在天梯比賽中逃跑,將會受到最大力度的扣分懲罰。
9. 每賽季結束後,24小時內根據玩家段位發放賽季獎勵。
10.每天參與天梯爭霸賽的上限次數為51次。]]
	Tlang["MODE_3"] = [[自由房間PVP]]
	Tlang["MODE_3_DES"] = [[1. 玩家可反復進行技巧教學
2. 完成教學任務可以獲得獎勵哦]]
	Tlang["MODE_4"] = [[技巧教學]]
	Tlang["MODE_5"] = [[彈道1V1
 大師賽]]
	Tlang["MODE_6"] = [[未開放]]
	Tlang["MODE_7"] = [[單人冒險]]
	Tlang["MODE_8"] = [[組隊遠征]]
	Tlang["MODE_9"] = [[天空之城]]
	Tlang["MONDAY"] = [[星期一]]
	Tlang["MOSTERS"] = [[出現的怪物]]
	Tlang["MPVE_NOENTRE"] = [[您不滿足進入該房間的條件,無法進入]]
	Tlang["MUL_PVE_OPEN"] = [[多人戰鬥(2V2,3V3)將在%d級開啟]]
	Tlang["MUSIC"] = [[音樂]]
	Tlang["MY_FIGHT"] = [[我的戰力]]
	Tlang["MY_SCORES"] = [[我的段位]]
	Tlang["NAME_LONG"] = [[角色名過長]]
	Tlang["NEED_LEVEL_OPEN"] = [[%d級開放此功能]]
	Tlang["NEED_STRE"] = [[您的活力不足]]
	Tlang["NEED_STRE_BUY"] = [[您的活力不足,是否購買?]]
	Tlang["NEED_UPDATE"] = [[有新的資源可以更新哦]]
	Tlang["NEWS"] = [[消息]]
	Tlang["NEW_NAME"] = [[點擊輸入新的名稱]]
	Tlang["NICK"] = [[角色名]]
	Tlang["NICK_FORMAT_ERROR"] = [[角色名格式錯誤]]
	Tlang["NORMAL_MANY"] = [[普通]]
	Tlang["NOT_OPEN"] = [[暫未開放,敬請期待]]
	Tlang["NO_EXIT_BATTLE"] = [[現在不能退出戰鬥]]
	Tlang["ObbCopyError"] = [[數據包拷貝失敗]]
	Tlang["ObbDownFaile"] = [[數據包下載失敗]]
	Tlang["ObbDownProgress"] = [[數據包下載進度%s]]
	Tlang["ObbDownSuccess"] = [[數據包下載成功]]
	Tlang["ObbOtherError"] = [[數據包其他錯誤]]
	Tlang["ObbUnZipFaile"] = [[數據包解壓失敗]]
	Tlang["ObbUnZipSuccess"] = [[數據包解壓成功]]
	Tlang["PACK"] = [[背包]]
	Tlang["PARTY_DUNGEON"] = [[組隊遠征]]
	Tlang["PASSWORD_FORMAT_ERROR"] = [[密碼格式錯誤]]
	Tlang["PASSWORD_PLACEHOLDER"] = [[密碼]]
	Tlang["PLAYERNAME"] = [[玩家名稱]]
	Tlang["PLAYER_OFFLINE"] = [[邀請的玩家不線上]]
	Tlang["POWER_STOP"] = [[你已被沉默,無法攻擊]]
	Tlang["PRACTISE"] = [[自由模式]]
	Tlang["PULS_POWER"] = [[可通過以下方式提升戰力]]
	Tlang["PVE_LEVEL"] = [[副本難度]]
	Tlang["PVE_NO_NUMEBERTIME"] = [[挑戰副本次數不足]]
	Tlang["PVE_NO_NUMEBERTIME2"] = [[您或者隊員挑戰副本次數不足]]
	Tlang["PVE_NUMBERTIME_BUY"] = [[挑戰副本次數不足,是否購買]]
	Tlang["QIEHUANZHANGHAO"] = [[切換帳號]]
	Tlang["QUICK_START"] = [[尋找房間]]
	Tlang["QUIT_BATTLE"] = [[該關卡還沒有完成,退出將不會得到獎勵,您要確定退出嗎?]]
	Tlang["RANDOM_MAP"] = [[隨機地圖]]
	Tlang["RANKING_0"] = [[定位賽]]
	Tlang["RANKING_1"] = [[鬥王1]]
	Tlang["RANKING_10"] = [[王者5]]
	Tlang["RANKING_11"] = [[鑽石1]]
	Tlang["RANKING_12"] = [[鑽石2]]
	Tlang["RANKING_13"] = [[鑽石3]]
	Tlang["RANKING_14"] = [[鑽石4]]
	Tlang["RANKING_15"] = [[鑽石5]]
	Tlang["RANKING_16"] = [[鉑金1]]
	Tlang["RANKING_17"] = [[鉑金2]]
	Tlang["RANKING_18"] = [[鉑金3]]
	Tlang["RANKING_19"] = [[鉑金4]]
	Tlang["RANKING_2"] = [[鬥王2]]
	Tlang["RANKING_20"] = [[鉑金5]]
	Tlang["RANKING_21"] = [[黃金1]]
	Tlang["RANKING_22"] = [[黃金2]]
	Tlang["RANKING_23"] = [[黃金3]]
	Tlang["RANKING_24"] = [[黃金4]]
	Tlang["RANKING_25"] = [[黃金5]]
	Tlang["RANKING_26"] = [[白銀1]]
	Tlang["RANKING_27"] = [[白銀2]]
	Tlang["RANKING_28"] = [[白銀3]]
	Tlang["RANKING_29"] = [[白銀4]]
	Tlang["RANKING_3"] = [[鬥王3]]
	Tlang["RANKING_30"] = [[白銀5]]
	Tlang["RANKING_31"] = [[青銅1]]
	Tlang["RANKING_32"] = [[青銅2]]
	Tlang["RANKING_33"] = [[青銅3]]
	Tlang["RANKING_34"] = [[青銅4]]
	Tlang["RANKING_35"] = [[青銅5]]
	Tlang["RANKING_4"] = [[鬥王4]]
	Tlang["RANKING_46"] = [[%s 將獲得以下獎勵]]
	Tlang["RANKING_47"] = [[賽季]]
	Tlang["RANKING_5"] = [[鬥王5]]
	Tlang["RANKING_50"] = [[我的戰績]]
	Tlang["RANKING_51"] = [[鬥王]]
	Tlang["RANKING_52"] = [[黃金]]
	Tlang["RANKING_53"] = [[白銀]]
	Tlang["RANKING_54"] = [[鉑金]]
	Tlang["RANKING_55"] = [[青銅]]
	Tlang["RANKING_56"] = [[鑽石]]
	Tlang["RANKING_57"] = [[王者]]
	Tlang["RANKING_6"] = [[王者1]]
	Tlang["RANKING_7"] = [[王者2]]
	Tlang["RANKING_8"] = [[王者3]]
	Tlang["RANKING_9"] = [[王者4]]
	Tlang["RANKING_DES"] = [[極品道具,每日參與即得,賽季獎勵,極品神器,王者象徵]]
	Tlang["RANKING_REWARD_DES"] = [[勇士,這是你本賽季的天梯結算獎勵,請笑納。]]
	Tlang["RANKING_REWARD_TITLE"] = [[天梯結算獎勵]]
	Tlang["RANKING_TALK_1"] = [[祝賀您已經晉升為%s]]
	Tlang["RANKING_TALK_2"] = [[您的段位已降至%s]]
	Tlang["RANKING_TALK_3"] = [[您的段位已晉升為%s]]
	Tlang["RANKING_TALK_4"] = [[您的段位已降為%s]]
	Tlang["RANKING_TALK_5"] = [[沒有段位不能獲得獎勵
 (需完成5場定位賽)]]
	Tlang["RANKING_TALK_6"] = [[定位賽完成,您的段位為%s]]
	Tlang["RANKING_TALK_7"] = [[祝您再接再厲,更上一層樓]]
	Tlang["RANK_COMPELET_TIMES"] = [[完成%s場天梯賽]]
	Tlang["RANK_VICTORY_TIMES"] = [[取得%s場天梯賽勝利]]
	Tlang["READY"] = [[準備]]
	Tlang["RECENTLY_ENTERED"] = [[最近進入]]
	Tlang["RECOMMEND_FIGHT"] = [[建議戰力]]
	Tlang["RECONNECT"] = [[正在斷線重連…]]
	Tlang["RECONNECT_FAILD"] = [[重連失敗,請重新登錄]]
	Tlang["REGIST"] = [[註冊]]
	Tlang["REGISTER_TEXT_1"] = [[不填寫郵箱,密碼丟失後將無法找回,是否確定完成註冊?]]
	Tlang["REGISTER_TEXT_10"] = [[確認重置帳號%s的密碼嗎? 將往該帳號綁定的郵箱發送重置密碼]]
	Tlang["REGISTER_TEXT_11"] = [[修改密碼]]
	Tlang["REGISTER_TEXT_12"] = [[是否確定修改密碼?]]
	Tlang["REGISTER_TEXT_13"] = [[新密碼]]
	Tlang["REGISTER_TEXT_14"] = [[舊密碼]]
	Tlang["REGISTER_TEXT_2"] = [[郵箱格式錯誤]]
	Tlang["REGISTER_TEXT_3"] = [[忘記密碼]]
	Tlang["REGISTER_TEXT_4"] = [[注:綁定郵箱過後不能隨意更改,如有需要請聯繫GM
    請綁定您的電子郵箱,電子郵箱綁定後,即可通過郵箱找回密碼]]
	Tlang["REGISTER_TEXT_5"] = [[每個郵箱只能對應一個帳號,如重複使用則不可綁定。]]
	Tlang["REGISTER_TEXT_6"] = [[綁定郵箱獲贈:]]
	Tlang["REGISTER_TEXT_7"] = [[帳號為空,或者該帳號沒有綁定郵箱,請重新檢查帳號是否正確,或者聯繫GM]]
	Tlang["REGISTER_TEXT_8"] = [[密碼已發送至您綁定的郵箱,請查收]]
	Tlang["REGISTER_TEXT_9"] = [[已綁定]]
	Tlang["REGIST_SUCCESS"] = [[註冊成功!]]
	Tlang["RELATIONSHIP"] = [[關係]]
	Tlang["RESET_FIGHT_TIMES"] = [[是否花費鑽石重置挑戰次數?
重置後挑戰次數恢復為%d次]]
	Tlang["RESET__FIGHT_PRICE"] = [[重置挑戰次數需消耗 %d<image>ui/icon/diamond.png</image>]]
	Tlang["RETRY"] = [[重試]]
	Tlang["ROLE"] = [[角色]]
	Tlang["ROLE_EXISTS"] = [[角色名已經存在]]
	Tlang["ROOM_HOST"] = [[房主]]
	Tlang["ROOM_TIPS_0"] = [[房間人數已滿]]
	Tlang["ROOM_TIPS_1"] = [[房間不存在]]
	Tlang["ROOM_TIPS_10"] = [[隊伍不存在]]
	Tlang["ROOM_TIPS_11"] = [[不是房主不能匹配]]
	Tlang["ROOM_TIPS_2"] = [[己方平均分]]
	Tlang["ROOM_TIPS_3"] = [[對方平均分]]
	Tlang["ROOM_TIPS_4"] = [[你沒有在此房間]]
	Tlang["ROOM_TIPS_5"] = [[玩家沒有此技能]]
	Tlang["ROOM_TIPS_6"] = [[玩家正在處理其他請求]]
	Tlang["ROOM_TIPS_7"] = [[邀請的人已經在房間內]]
	Tlang["ROOM_TIPS_8"] = [[隊伍已經在匹配中]]
	Tlang["ROOM_TIPS_9"] = [[有玩家還沒准備好,不能開始匹配]]
	Tlang["ROOM_WAIT_ALL"] = [[房間中還有玩家未準備]]
	Tlang["ROUND"] = [[第%d回合]]
	Tlang["SATURDAY"] = [[星期六]]
	Tlang["SERVER_ERROR"] = [[伺服器返回錯誤]]
	Tlang["SERVER_MAINTENANCE"] = [[伺服器正在維護,請稍後登錄…]]
	Tlang["SERVER_NUM"] = [[%s 服]]
	Tlang["SERVER_RECHARGE"] = [[增加次數還需要充值%d鑽石]]
	Tlang["SERVER_STATE_CROWD"] = [[擁擠]]
	Tlang["SERVER_STATE_HOT"] = [[火爆]]
	Tlang["SERVER_STATE_MAINTAIN"] = [[維護]]
	Tlang["SERVER_STATE_NEW"] = [[新服]]
	Tlang["SERVER_STATE_NORMAL"] = [[正常]]
	Tlang["SERVER_WRONG_ANY"] = [[鑽石不足]]
	Tlang["SERVICE_10"] = [[網路異常,更新出錯,需要修復客戶端]]
	Tlang["SETTING"] = [[設置]]
	Tlang["SETTING_RECOMMEND"] = [[推薦力度]]
	Tlang["SHENGYUTIANSHU"] = [[您的月卡還有<style color:#76d034>%d天</style>到期]]
	Tlang["SHIFOUCHONGZHI"] = [[鑽石不足,是否充值?]]
	Tlang["SKILL"] = [[技能]]
	Tlang["SKILLS_SKILLS"] = [[技能選擇]]
	Tlang["SOME_TIPS"] = [[有新武器了?別忘了去裝備上哦!
記得每天12點,18點和21點都可以在每日活動中領取50點活力哦
完成每日必做任務可以使你快速增強,千萬不要忘記哦!
黑市商人出現2小時後就會離開,在他離開之前趕快瘋狂搶購吧!
武器地獄可以啟動"地獄機甲"形態
武器地獄的必殺技可以讓一定區域內所有敵人受到傷害
武器死神鐮刀可以啟動"死神"形態
武器死神鐮刀的必殺技可以降低敵人的防禦
武器格林拳套的必殺技可以讓敵人持續受傷
武器風神斧的必殺技可以降低敵人的怒氣
武器聖光之錘可以啟動"大天使守護"形態
武器聖光之錘的必殺技可以清除己方成員的負面效果(比如中毒,冰凍)
武器離子加農炮的必殺技可以使敵人無法釋放技能
武器魔導加特林可以啟動"加特林機甲"形態
武器魔導加特林的必殺技對地面不造成彈坑
真想不到冰凍自己可以免受敵人的傷害!
軍銜達到軍士長並且擁有足夠的掃蕩卷,就可以對副本進行連續掃蕩,無需經過戰鬥場景
如果你想退出戰鬥,點擊右上角地圖下麵的齒輪按鈕,然後點擊退出戰鬥
戰鬥失敗後,可通過提升等級,武器進階,時裝洗煉,祝福等來提升實力
當你等級達到10級後,可以花費500鑽石創建一個屬於你的公會哦
通過公會捐獻以及完成公會任務可獲得公會幣
點擊人物頭像,進入設置頁面,點擊右下角可切換帳號
軍銜達到上士並且擁有掃蕩卷,就可以對副本進行單次掃蕩,無需經過戰鬥場景
單人冒險每次消耗6點活力,BOSS關卡消耗10點活力。
點擊公會管理中的公會設置,即可設置玩家加入公會最小角色等級
記住你的帳號和密碼,這樣你可以在不同設備之間玩遊戲.
距離可以通過右上角小地圖中標尺來測量
高拋打法:角度=90度-距離+風力(順風正數,逆風負數),力度=95
覺得自己屬性不足?趕快去找導師幫你訓練一下吧
好好對待自己的寵物,它對你的幫助會很大的
時裝的所有屬性洗煉至相同並且達到MAX,就可以啟動隱藏屬性
時裝的套裝屬性啟動順序:服飾—帽子—髮型—表情—臉飾—套裝—服飾
只有被穿戴上的時裝才能啟動套裝屬性
套裝原色分為:日,月,星,水,電
2個相同套裝元素的時裝能夠按順序啟動其他部位]]
	Tlang["SP_BOUGHT"] = [[今日剩餘次數:%d/%d]]
	Tlang["SP_BOUGHT_END"] = [[今日可購買活力次數已用完,每日可購買次數請在軍銜系統查看。]]
	Tlang["SP_BOUGHT_TIMES"] = [[已購買活力次數]]
	Tlang["SP_BUY"] = [[每消耗1點活力可獲取6點經驗]]
	Tlang["SP_BUY_JX"] = [[軍銜升級到<style color: #ffff00>%s</style> ,可增加額外%s次次數。]]
	Tlang["SP_BUY_TITLE"] = [[購買活力]]
	Tlang["SP_EXPEND"] = [[已消耗活力數量]]
	Tlang["SP_PRICE"] = [[購買%d<image>ui/icon/lightning.png</image>需要消耗%d<image>ui/icon/diamond.png</image>]]
	Tlang["SQ_TIPS_1"] = [[沒有神器範本]]
	Tlang["SQ_TIPS_2"] = [[神器精華不足]]
	Tlang["SQ_TIPS_3"] = [[武器碎片不足]]
	Tlang["SUNDAY"] = [[星期日]]
	Tlang["SWEEP_BUY"] = [[您的掃蕩卷不足
是否花費鑽石進行掃蕩?]]
	Tlang["SWEEP_ERROR"] = [[掃蕩錯誤]]
	Tlang["SWEEP_PRICE_1"] = [[掃蕩%d次需消耗%d<image>ui/icon/diamond.png</image>]]
	Tlang["SWEEP_PRICE_2"] = [[掃蕩%d次需消耗%d<image>ui/icon/diamond.png</image>+%d<image>icon/sweep_paper.png</image>]]
	Tlang["SWEEP_REWARDS"] = [[掃蕩獎勵]]
	Tlang["SWEEP_SEVERAL"] = [[連續掃蕩]]
	Tlang["SWEEP_TIMES"] = [[掃蕩%d次]]
	Tlang["SYSTEM_REPAIR"] = [[修復客戶端]]
	Tlang["SYSTEM_REPAIR_COMFIRM"] = [[確認修復此客戶端嗎？]]
	Tlang["SYSTEM_SETTING"] = [[系統設置]]
	Tlang["TARGET_OPEN_DESC_1"] = [[想知道誰給你發了資訊嗎?這裏可以看哦!]]
	Tlang["TARGET_OPEN_DESC_10"] = [[缺什麼東西嗎?去商城看看吧!]]
	Tlang["TARGET_OPEN_DESC_11"] = [[神秘的商店,各種稀有物品都會在這裏出現哦!]]
	Tlang["TARGET_OPEN_DESC_12"] = [[你在排行榜上排名第幾?去榮耀殿堂看看就知道了]]
	Tlang["TARGET_OPEN_DESC_13"] = [[探索符文聖地,裝備符文,可以提升自己的屬性哦!]]
	Tlang["TARGET_OPEN_DESC_14"] = [[這裏盛產符文,能不能得到,可全靠你自己啦]]
	Tlang["TARGET_OPEN_DESC_15"] = [[低級符文合成高級符文,你還不心動?]]
	Tlang["TARGET_OPEN_DESC_16"] = [[讓你和一幫兄弟打造萬世基業!]]
	Tlang["TARGET_OPEN_DESC_17"] = [[讓你的裝備擁有額外的屬性]]
	Tlang["TARGET_OPEN_DESC_18"] = [[祝福能讓你變得更強力]]
	Tlang["TARGET_OPEN_DESC_19"] = [[你不知道有一直寵物是一件多麼炫酷的事情?]]
	Tlang["TARGET_OPEN_DESC_2"] = [[查看你所擁有的所有物品]]
	Tlang["TARGET_OPEN_DESC_20"] = [[讓美女導師來訓練你,讓你變得更厲害]]
	Tlang["TARGET_OPEN_DESC_21"] = [[神器,聽名字也知道,你絕對值得擁有]]
	Tlang["TARGET_OPEN_DESC_22"] = [[掌握戰鬥技巧最快速的途徑]]
	Tlang["TARGET_OPEN_DESC_23"] = [[玩膩了一個人戰鬥?去試試組隊和人戰鬥吧]]
	Tlang["TARGET_OPEN_DESC_24"] = [[和朋友組隊,一起遠征,挑戰極限吧!]]
	Tlang["TARGET_OPEN_DESC_3"] = [[你有什麼技能都可以在這裏看看]]
	Tlang["TARGET_OPEN_DESC_4"] = [[每把武器都有不一樣的必殺技,搜集更多武器,就能有更多與眾不同的玩法]]
	Tlang["TARGET_OPEN_DESC_5"] = [[查看角色的屬性,還能查看時裝哦!]]
	Tlang["TARGET_OPEN_DESC_6"] = [[你的裝備夠強力嗎?這裏查看裝備的級別和品階]]
	Tlang["TARGET_OPEN_DESC_7"] = [[顧名思義,完成這些目標能讓你快速成長,還有很多獎勵等你來拿]]
	Tlang["TARGET_OPEN_DESC_8"] = [[所有和你有關的人都在這裏了]]
	Tlang["TARGET_OPEN_DESC_9"] = [[既然是每天都要做的事,獎勵怎麼可能不豐厚]]
	Tlang["TARGET_OPEN_DES_25"] = [[有心儀的對象了嗎?快向她求婚吧!]]
	Tlang["TARGET_OPEN_DES_26"] = [[迴圈任務可以給你豐富的獎勵。]]
	Tlang["TARGET_OPEN_DES_27"] = [[想要的物品都可以在這裏淘到哦。]]
	Tlang["TARGET_OPEN_NAME_1"] = [[消息]]
	Tlang["TARGET_OPEN_NAME_10"] = [[商城]]
	Tlang["TARGET_OPEN_NAME_11"] = [[神秘商城]]
	Tlang["TARGET_OPEN_NAME_12"] = [[榮譽殿堂]]
	Tlang["TARGET_OPEN_NAME_13"] = [[符文系統]]
	Tlang["TARGET_OPEN_NAME_14"] = [[符文探索]]
	Tlang["TARGET_OPEN_NAME_15"] = [[符文合成]]
	Tlang["TARGET_OPEN_NAME_16"] = [[公會]]
	Tlang["TARGET_OPEN_NAME_17"] = [[洗煉]]
	Tlang["TARGET_OPEN_NAME_18"] = [[裝備祝福]]
	Tlang["TARGET_OPEN_NAME_19"] = [[寵物]]
	Tlang["TARGET_OPEN_NAME_2"] = [[背包]]
	Tlang["TARGET_OPEN_NAME_20"] = [[導師訓練]]
	Tlang["TARGET_OPEN_NAME_21"] = [[神器]]
	Tlang["TARGET_OPEN_NAME_22"] = [[技巧教學]]
	Tlang["TARGET_OPEN_NAME_23"] = [[競技場]]
	Tlang["TARGET_OPEN_NAME_24"] = [[組隊遠征]]
	Tlang["TARGET_OPEN_NAME_25"] = [[婚姻殿堂]]
	Tlang["TARGET_OPEN_NAME_26"] = [[迴圈任務]]
	Tlang["TARGET_OPEN_NAME_27"] = [[拍賣行]]
	Tlang["TARGET_OPEN_NAME_3"] = [[技能]]
	Tlang["TARGET_OPEN_NAME_4"] = [[武器]]
	Tlang["TARGET_OPEN_NAME_5"] = [[角色]]
	Tlang["TARGET_OPEN_NAME_6"] = [[裝備]]
	Tlang["TARGET_OPEN_NAME_7"] = [[成長目標]]
	Tlang["TARGET_OPEN_NAME_8"] = [[關係]]
	Tlang["TARGET_OPEN_NAME_9"] = [[每日必做]]
	Tlang["TARGET_OPEN_OPENED"] = [[已經開啟]]
	Tlang["TASK"] = [[任務]]
	Tlang["THURSDAY"] = [[星期四]]
	Tlang["TILILINGQU"] = [[活力領取]]
	Tlang["TIMES"] = [[掃蕩%d次共獲得]]
	Tlang["TIPS_VERSION_LOW"] = [[當前版本過低, 請下載新的客戶端]]
	Tlang["TRAGET_STORNG_MAINDES_1"] = [[累積足夠的升級經驗就能提升角色等級,提升角色等級可增加角色基礎屬性。]]
	Tlang["TRAGET_STORNG_MAINDES_2"] = [[累積榮譽晉升軍銜,可開啟各種特權,並可獲得擁有強大屬性的專屬徽章。]]
	Tlang["TRAGET_STORNG_MAINDES_3"] = [[裝備培養可獲得強大的戰鬥屬性,強化和進階是必不可少的培養方式。]]
	Tlang["TRAGET_STORNG_MAINDES_4"] = [[收集各種屬性符文,穿戴後即可獲得符文提供的屬性。]]
	Tlang["TRAGET_STORNG_MAINDES_5"] = [[武器進階,魂器升級,不單單是屬性成長,還能改變武器外觀。]]
	Tlang["TRAGET_STORNG_MAINDES_6"] = [[時裝收集,穿戴,洗煉,部位祝福都能增加戰鬥屬性,同時還能彰顯個性裝扮。]]
	Tlang["TRAGET_STORNG_MAINDES_7"] = [[公會科技,公會獨有,快加入公會大家庭,一起研究學習吧。]]
	Tlang["TRAGET_STORNG_MAINDES_8"] = [[萌寵不但可以協同主人作戰,更能將自身屬性轉換給主人。]]
	Tlang["TRAGET_STORNG_MAINDES_9"] = [[完成導師訓練,永久獲得專屬導師的屬性成長。]]
	Tlang["TRAGET_STORNG_MAINNAME_1"] = [[等級提升]]
	Tlang["TRAGET_STORNG_MAINNAME_10"] = [[華麗羽翼]]
	Tlang["TRAGET_STORNG_MAINNAME_11"] = [[我要材料]]
	Tlang["TRAGET_STORNG_MAINNAME_2"] = [[晉升軍銜]]
	Tlang["TRAGET_STORNG_MAINNAME_3"] = [[裝備培養]]
	Tlang["TRAGET_STORNG_MAINNAME_4"] = [[神秘符文]]
	Tlang["TRAGET_STORNG_MAINNAME_5"] = [[神兵利器]]
	Tlang["TRAGET_STORNG_MAINNAME_6"] = [[個性時裝]]
	Tlang["TRAGET_STORNG_MAINNAME_7"] = [[公會科技]]
	Tlang["TRAGET_STORNG_MAINNAME_8"] = [[萌寵養成]]
	Tlang["TRAGET_STORNG_MAINNAME_9"] = [[導師訓練]]
	Tlang["TRAGET_STORNG_SUBNAME_1"] = [[每日必做]]
	Tlang["TRAGET_STORNG_SUBNAME_10"] = [[符文探索]]
	Tlang["TRAGET_STORNG_SUBNAME_11"] = [[符文穿戴]]
	Tlang["TRAGET_STORNG_SUBNAME_12"] = [[符文合成]]
	Tlang["TRAGET_STORNG_SUBNAME_13"] = [[武器收集]]
	Tlang["TRAGET_STORNG_SUBNAME_14"] = [[魂器升級]]
	Tlang["TRAGET_STORNG_SUBNAME_15"] = [[神器突破]]
	Tlang["TRAGET_STORNG_SUBNAME_16"] = [[時裝裝扮]]
	Tlang["TRAGET_STORNG_SUBNAME_17"] = [[衣櫃屬性]]
	Tlang["TRAGET_STORNG_SUBNAME_18"] = [[時裝洗煉]]
	Tlang["TRAGET_STORNG_SUBNAME_19"] = [[時裝祝福]]
	Tlang["TRAGET_STORNG_SUBNAME_2"] = [[競技練習]]
	Tlang["TRAGET_STORNG_SUBNAME_20"] = [[科技研發]]
	Tlang["TRAGET_STORNG_SUBNAME_21"] = [[科技學習]]
	Tlang["TRAGET_STORNG_SUBNAME_22"] = [[寵物評級]]
	Tlang["TRAGET_STORNG_SUBNAME_23"] = [[寵物等級]]
	Tlang["TRAGET_STORNG_SUBNAME_24"] = [[寵物品質]]
	Tlang["TRAGET_STORNG_SUBNAME_25"] = [[寵物星級]]
	Tlang["TRAGET_STORNG_SUBNAME_26"] = [[寵物天賦]]
	Tlang["TRAGET_STORNG_SUBNAME_27"] = [[寵物技能]]
	Tlang["TRAGET_STORNG_SUBNAME_28"] = [[金幣]]
	Tlang["TRAGET_STORNG_SUBNAME_29"] = [[鑽石]]
	Tlang["TRAGET_STORNG_SUBNAME_3"] = [[單人關卡]]
	Tlang["TRAGET_STORNG_SUBNAME_30"] = [[榮譽]]
	Tlang["TRAGET_STORNG_SUBNAME_31"] = [[活力]]
	Tlang["TRAGET_STORNG_SUBNAME_32"] = [[公會幣]]
	Tlang["TRAGET_STORNG_SUBNAME_33"] = [[掃蕩卷]]
	Tlang["TRAGET_STORNG_SUBNAME_34"] = [[時裝]]
	Tlang["TRAGET_STORNG_SUBNAME_35"] = [[洗煉石]]
	Tlang["TRAGET_STORNG_SUBNAME_36"] = [[祝福石]]
	Tlang["TRAGET_STORNG_SUBNAME_37"] = [[羽毛]]
	Tlang["TRAGET_STORNG_SUBNAME_38"] = [[武器碎片]]
	Tlang["TRAGET_STORNG_SUBNAME_39"] = [[鬥魂]]
	Tlang["TRAGET_STORNG_SUBNAME_4"] = [[組隊副本]]
	Tlang["TRAGET_STORNG_SUBNAME_40"] = [[神器精華]]
	Tlang["TRAGET_STORNG_SUBNAME_41"] = [[強化石]]
	Tlang["TRAGET_STORNG_SUBNAME_42"] = [[進階石]]
	Tlang["TRAGET_STORNG_SUBNAME_43"] = [[魔導石]]
	Tlang["TRAGET_STORNG_SUBNAME_44"] = [[進階材料]]
	Tlang["TRAGET_STORNG_SUBNAME_45"] = [[符文]]
	Tlang["TRAGET_STORNG_SUBNAME_46"] = [[符文石]]
	Tlang["TRAGET_STORNG_SUBNAME_47"] = [[寵物精華]]
	Tlang["TRAGET_STORNG_SUBNAME_48"] = [[寵物糧食]]
	Tlang["TRAGET_STORNG_SUBNAME_49"] = [[高級資質丹]]
	Tlang["TRAGET_STORNG_SUBNAME_5"] = [[競技練習]]
	Tlang["TRAGET_STORNG_SUBNAME_50"] = [[資質丹]]
	Tlang["TRAGET_STORNG_SUBNAME_51"] = [[寵物手冊]]
	Tlang["TRAGET_STORNG_SUBNAME_52"] = [[技能書]]
	Tlang["TRAGET_STORNG_SUBNAME_53"] = [[頂級扭蛋]]
	Tlang["TRAGET_STORNG_SUBNAME_54"] = [[普通訓練靶]]
	Tlang["TRAGET_STORNG_SUBNAME_55"] = [[高級訓練靶]]
	Tlang["TRAGET_STORNG_SUBNAME_6"] = [[天梯競技]]
	Tlang["TRAGET_STORNG_SUBNAME_7"] = [[遊戲充值]]
	Tlang["TRAGET_STORNG_SUBNAME_8"] = [[裝備強化]]
	Tlang["TRAGET_STORNG_SUBNAME_9"] = [[裝備進階]]
	Tlang["TUESDAY"] = [[星期二]]
	Tlang["UNAUTHORIZE"] = [[未授權用戶]]
	Tlang["UPDATE_ERROR"] = [[親,您的網路出問題啦,資源更新失敗,請確保網路狀況良好後重試]]
	Tlang["UPDATE_FINISH"] = [[更新完畢]]
	Tlang["USER_NAME_PLACEHOLDER"] = [[用戶名]]
	Tlang["USER_ONLINE"] = [[該用戶已線上,若遇斷線重連,請10秒後重新嘗試登錄]]
	Tlang["USE_POWER"] = [[消耗活力]]
	Tlang["VIP_RANK"] = [[進階下一級需要消耗%d<image>ui/icon/diamond.png</image>,是否進階？]]
	Tlang["Voice_AutoPlay"] = [[語音自動播放設置]]
	Tlang["Voice_Exit"] = [[鬆開手指,取消發送]]
	Tlang["Voice_Input"] = [[手指滑開,取消發送]]
	Tlang["Voice_Time"] = [[%d秒]]
	Tlang["WARNING"] = [[系統檢測出您有可疑操作,您即將被強制登出遊戲。]]
	Tlang["WEDNESDAY"] = [[星期三]]
	Tlang["WIN_3"] = [[三連勝]]
	Tlang["WIN_MAX"] = [[最高連勝]]
	Tlang["WIN_RATE"] = [[勝率]]
	Tlang["WORLD"] = [[世界地圖]]
	Tlang["WORLD_SPEAK_1"] = [[軍銜%s以下不能發言]]
	Tlang["WOYAOCHONGZHI"] = [[我要充值]]
	Tlang["XIANYICI"] = [[限一次]]
	Tlang["YILINGQU"] = [[已領取]]
	Tlang["YIQIANDAO"] = [[已簽到]]
	Tlang["YUANZHENGMATOU"] = [[遠征港口]]
	Tlang["YUEKAMIAOSU"] = [[立刻獲得280<image>ui/icon/diamond.png</image>
隨後30天內每天可領取70<image>ui/icon/diamond.png</image>]]
	Tlang["rewards_reason_194"] = [[死亡秘境本周結算]]
