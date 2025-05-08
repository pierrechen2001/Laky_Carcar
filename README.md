# 🚗 Laky Carcar

A puzzle game built with C++ and SFML, inspired by the classic "Get Out the Parking Lot" board game — now with special effects, time/step limits, and a full graphical interface.

這是一款以《移出停車場》為靈感的電腦益智遊戲，使用 C++ 開發，搭配 SFML 實作滑鼠互動與圖形化介面，並加入多種挑戰限制與特殊物件，讓遊戲更有層次與趣味。

---

## 🎮 Game Features | 遊戲特色

- 🧩 Puzzle Mechanics – 移動車輛解開道路，讓紅車通關
- 🧱 Collision Logic – 碰撞與障礙物偵測，需巧妙操作
- 🕹 GUI with SFML – 滑鼠點擊互動，操作直覺
- ⏱ Limit System – 加入步數限制、時間限制、陷阱區域（Lake、Frog、Turtle）
- 📁 File I/O – 關卡讀取與車輛配置支援自定義
- 🔁 OOP Design – 使用多型與繼承設計 Car & Limit 類別架構

---

## 🛠 Architecture | 程式架構

### `Car` class  
每台車的方向、長度、顏色、座標皆封裝於類別中，並可繼承進一步擴充行為

### `Limit` class  
特殊限制物件抽象類別，包含：
- `Lake`: 行動區域限制（誤入即結束）
- `Frog`: 步數限制（類似妙蛙種子追逐）
- `Turtle`: 時間限制（在傑尼龜之前完成）

---

## 💡 Dev Notes | 開發筆記

- 使用 SFML 繪製圖形介面，處理滑鼠事件與畫面更新
- 車輛與障礙皆以 `ParkingSpace` 陣列為邏輯依據
- 精心設計每個關卡的難度與邏輯路徑
- 支援關卡編輯與關卡文件解析（文字檔）

---

## 🧠 Future Improvements | 未來展望

- 🎨 3D 化場景與物件
- 👤 加入行人等進階限制
- 🔊 音效與動畫演出強化沉浸感
- 📦 更完善的關卡管理系統與 UI 設計

---

## 👨‍💻 Team Members | 團隊成員

- 👑 陳冠宇 Pierre（介面工程）
- 🧠 蔡政穎 Stonk（後端邏輯開發）
- 🔗 黃聖家 Iris（前後端整合）
- 🎨 汪芷瑩 Kelly（協作與美術）

---

> 💬 *A class project with big ambitions — fun, logic, and teamwork collide at Laky Carcar.*
> https://deepwiki.com/pierrechen2001/Laky_Carcar/1.2-system-architecture
