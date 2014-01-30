ST7735
======

<b>ST7735 driver and library for STM32F3DISCOVEY board</b><br>
<p>The idea has been taken from Arduino Adafruit and UTFT sources. The arduino code has been ported for STM32F3 controller.</p>
<p>Standard libraries like CMSIS, Pheriperal, etc are not included</p>
 <h2>Initialization</h2>
<b>Initialization for ST7735B LCD (B&amp;W)</b><br>
void lcd7735_initB(void);<br>
<br>
<b>Initialization for ST7735R LCD (green or red tabs)</b><br>
extern void lcd7735_initR(uint8_t options);<br>
<br>
<h2>Graphics function</h2>
<b> Fill screen by selected color.</b><br>
&nbsp;void lcd7735_fillScreen(uint16_t color);<br>
<b>Draw color rectangular on screen. The x1,y1 is top left corner
and x2,y2 bottom right corner on screen.</b><br>
void lcd7735_drawRect(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,
uint16_t color);<br>
<b>Fill color rectangular on screen. The x1,y1 is top left corner
and x2,y2 bottom right corner on screen.</b><br>
extern void lcd7735_fillRect(int16_t x, int16_t y, int16_t width,
int16_t height, uint16_t color);<br>
<b>Draw color pixel on screen.</b><br>
void lcd7735_drawPixel(int16_t x, int16_t y, uint16_t color);<br>
<b>Draw horizontal line with specified parameters.</b><br>
void lcd7735_drawFastHLine(int16_t x, int16_t y, int16_t width,
uint16_t color);<br>
<b>Draw horizontal line with specified parameters.</b><br>
void lcd7735_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t
color);<br>
<b>Draw any line with specified parameters.</b><br>
void lcd7735_drawFastLine(uint8_t x1, uint8_t y1, uint8_t x2,
uint8_t y2, uint16_t color);<br>
<b> Draw color circle on screen. </b><br>
void lcd7735_drawCircle(int16_t x, int16_t y, int radius, uint16_t
color);<br>
<b> Fill color circle on screen.</b><br>
void lcd7735_fillCircle(int16_t x, int16_t y, int radius, uint16_t
color);<br>
<b> Render bitmap on screen. The x1,y1 is top left corner. The
“scale” – integer values for multiply bitmap size.</b><br>
void lcd7735_drawBitmap(int x, int y, int sx, int sy, bitmapdatatype
data, int scale);<br>
<b> The same but rotated.</b><br>
void lcd7735_drawBitmapRotate(int x, int y, int sx, int sy,
bitmapdatatype data, int deg, int rox, int roy);<br>
<h2> Service functions</h2>
<b> Get sizes of matrix in pixels</b><br>
uint8_t lcd7735_getWidth(void);<br>
uint8_t lcd7735_getHeight(void);<br>
<b> Invert screen, parameters: INVERT_ON/ INVERT_OFF</b><br>
void lcd7735_invertDisplay(const uint8_t mode);<br>
<b> Pass 8-bit (each) R,G,B, get back 16-bit packed color</b><br>
uint16_t lcd7735_Color565(uint8_t r, uint8_t g, uint8_t b);<br>
<b> Rotate screen clockwise.&nbsp; Possible values:</b><b><br>
</b><b> </b>
<table cellpadding="2" cellspacing="2" border="1">
<tbody>
<tr>
<td><b>Parameter,</b></td>
<td><b>Degree</b></td>
</tr>
<tr>
<td><b>PORTRAIT,</b></td>
<td><b>0</b></td>
</tr>
<tr>
<td><b>LANDSAPE,</b></td>
<td><b>90</b></td>
</tr>
<tr>
<td><b>PORTRAIT_FLIP,</b></td>
<td><b>190</b></td>
</tr>
<tr>
<td><b>LANDSAPE_FLIP,</b></td>
<td><b>270</b></td>
</tr>
</tbody>
</table>
<b> </b>&nbsp; void lcd7735_setRotation(uint8_t m);<br>
<h2> <b>Arduino UTFT ported character render functions</b></h2>
<b> Set current font for lcd7735_print()</b><br>
void lcd7735_setFont(uint8_t* font);<br>
<b> Set transparency for lcd7735_print(), if “set” == 1 </b><br>
void lcd7735_setTransparent(uint8_t&nbsp; set);<br>
<b> Set current foreground color for lcd7735_print()</b><br>
void lcd7735_setForeground(uint16_t&nbsp; fg_color);<br>
<b> Set current background color for lcd7735_print()</b><br>
void lcd7735_setBackground(uint16_t&nbsp; bg_colol);<br>
<b> Print text on screen starting from x,y position with appropriate
degree </b><br>
&nbsp;void lcd7735_print(char *st, int x, int y, int deg);<br>
<h2><b> Emulation of TTY ASCII green-screen terminal &nbsp;</b></h2>
<b> Initialize LCD for emulation</b><br>
void lcd7735_init_screen(void *font,uint16_t fg, uint16_t bg,
uint8_t orientation);<br>
<b> Put single char of text line on terminal. The only ‘\n’ is
emulated as CRLF.</b><br>
void lcd7735_puts(char *str);<br>
void lcd7735_putc(char c);<br>
<br>
<i><h3>Notes</h3></i>
<p>
- The standard printf functionality is redirected if will use Redirect.c<br>
- Two preprocessor defines are used to reducing code size in this mode:<br>
<b>ONLY_TERMINAL_EMULATOR</b> - excludes all graphics functions<br>
<b>ONLY_SMALL_FONT</b> - excludes Big and SevenSeg fonts<br>
<br>
</p>
<p>Please see hw_config.h for hardware settings.
You have to carefuly setup INVEC table due to ST7735 is used SysTick for programing delays.</p>

<br>
<a href="http://youtu.be/13At83AL1kw"><b><u>Demo video</u></b></a>
