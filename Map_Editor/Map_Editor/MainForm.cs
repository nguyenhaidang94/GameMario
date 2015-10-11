using Map_Editor.Objects;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Map_Editor
{
    public partial class MainForm : Form
    {
        //doi tuong map
        private MapObject _MapObj;

        //picture box dung de ve
        private PictureBox _pbBackground;

        //danh sach picture box chua anh cua enemy
        private List<PictureBox> _ListPicbox;

        //enemy duoc chon
        private PictureBox _SelectedPicbox;

        //xac dinh chuot duoc nhan va di chuyen
        private bool _IsMouseDown;

        //doi tuong dang duoc chon
        private TileObject _SelectedObj;

        //điểm đầu và điểm cuối vẽ ground
        private Point _startPoint;
        private Point _endPoint;


        //constructor
        public MainForm()
        {
            InitializeComponent();
            _MapObj = new MapObject();
            InitListPb();
            _IsMouseDown = false;
            _SelectedObj = null;
            _startPoint = new Point();
            _endPoint = new Point();
        }

        //khoi tao background
        private void InitBackground()
        {
            _pnlDrawMap.Controls.Clear();
            _MapObj.ListGround.Clear();
            _MapObj.ListEnemy.Clear();

            _pbBackground = new PictureBox();
            _pbBackground.Width = _MapObj.MapColumn * MapObject.COLUMN_SIZE;
            _pbBackground.Height = _MapObj.MapRow * MapObject.ROW_SIZE;
            _MapObj.ArrTileNumber = new int[_MapObj.MapRow][];
            for (int i = 0; i < _MapObj.MapRow; i++)
                _MapObj.ArrTileNumber[i] = new int[_MapObj.MapColumn];
            _pbBackground.Paint += pbBackground_Paint;

            _pbBackground.MouseDown += pbBackground_MouseDown;
            _pbBackground.MouseUp += pbBackground_MouseUp;
            _pbBackground.MouseMove += pbBackground_MouseMove;

            _pnlDrawMap.Controls.Add(_pbBackground);
        }

        //khoi tao danh sach picture box chua anh cua enemy
        private void InitListPb()
        {
            _ListPicbox = new List<PictureBox>();
            _ListPicbox.Add(_pbEraser);
            _ListPicbox.Add(_pbLand);
            _ListPicbox.Add(_pbTile1);
            _ListPicbox.Add(_pbTile2);
            _ListPicbox.Add(_pbTile3);
            _ListPicbox.Add(_pbTile2);
            _ListPicbox.Add(_pbTile3);
            _ListPicbox.Add(_pbTile4);
            _ListPicbox.Add(_pbTile5);
            _ListPicbox.Add(_pbTile6);
            _ListPicbox.Add(_pbTile7);
            _ListPicbox.Add(_pbTile8);
            _ListPicbox.Add(_pbTile5);
            _ListPicbox.Add(_pbTile8);
            _ListPicbox.Add(_pbTile9);
            _ListPicbox.Add(_pbTile10);
            _ListPicbox.Add(_pbTile11);
            _ListPicbox.Add(_pbTile12);
            _ListPicbox.Add(_pbTile13);
            _ListPicbox.Add(_pbItem1);
            _ListPicbox.Add(_pbItem2);
            _ListPicbox.Add(_pbItem3);
            _ListPicbox.Add(_pbItem4);
            _ListPicbox.Add(_pbItem5);
            _ListPicbox.Add(_pbItem6);
            _ListPicbox.Add(_pbItem7);
            _ListPicbox.Add(_pbItem8);
            _ListPicbox.Add(_pbItem9);
            _ListPicbox.Add(_pbEnemy1);
            _ListPicbox.Add(_pbEnemy2);
            _ListPicbox.Add(_pbEnemy3);
            _ListPicbox.Add(_pbEnemy4);
            _ListPicbox.Add(_pbEnemy5);
            _ListPicbox.Add(_pbEnemy6);
            _ListPicbox.Add(_pbEnemy7);
            _ListPicbox.Add(_pbEnemy8);

            foreach (PictureBox pb in _ListPicbox)
                pb.Click += pictureBox_Click;

            _pbEraser.Click += pictureBox_Click;

            _SelectedPicbox = _pbTile1;
            _SelectedPicbox.BackColor = SystemColors.MenuHighlight;
        }

        //ve dong, cot
        private void DrawLine(Graphics g)
        {
            Pen pen = new Pen(Color.Red, 1.0f);
            pen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dot;

            for (int i = 0; i <= _MapObj.MapRow; i++)
                g.DrawLine(pen, new Point(0, i * MapObject.COLUMN_SIZE), new Point(_MapObj.MapColumn * MapObject.ROW_SIZE, i * MapObject.COLUMN_SIZE));
            for (int i = 0; i <= _MapObj.MapColumn; i++)
                g.DrawLine(pen, new Point(i * MapObject.COLUMN_SIZE, 0), new Point(i * MapObject.ROW_SIZE, _MapObj.MapRow * MapObject.ROW_SIZE));
        }

        //ghi file enemy
        private bool WriteFile(string path)
        {
            System.IO.StreamWriter sw = null;

            try
            {
                sw = new System.IO.StreamWriter(path);
            }
            catch
            {
                return false;
            }

            int mapHeight = _MapObj.MapRow * MapObject.ROW_SIZE;

            try
            {
                foreach (TileObject tileObj in _MapObj.ListGround)
                    sw.WriteLine(
                        tileObj.Id.ToString() + " "
                         + tileObj.TilePoint.X.ToString() + " "
                         + (mapHeight - tileObj.TilePoint.Y).ToString() + " "
                         + tileObj.TileSize.Width.ToString()
                         );

                foreach (TileObject tileObj in _MapObj.ListEnemy)
                {
                    if (string.IsNullOrEmpty(tileObj.Note))
                        sw.WriteLine(
                            tileObj.Id.ToString() + " "
                             + tileObj.TilePoint.X.ToString() + " "
                             + (mapHeight - tileObj.TilePoint.Y).ToString() + " "
                             + "-1"
                             );
                    else
                        sw.WriteLine(
                            tileObj.Id.ToString() + " "
                             + tileObj.TilePoint.X.ToString() + " "
                             + (mapHeight - tileObj.TilePoint.Y).ToString() + " "
                             + tileObj.Note
                             );
                }
            }
            catch
            {
                sw.Close();
                return false;
            }
            finally
            {
                sw.Close();
            }
            return true;
        }

        //doc file enemy
        private void ReadFile(string path)
        {
            StreamReader sr = null;

            int temp = 0;
            int id = 0;
            int x = 0;
            int y = 0;

            try
            {
                sr = new StreamReader(path);
            }
            catch
            {
                System.Windows.Forms.MessageBox.Show("Không đọc được file");
                return;
            }

            if (sr == null)
                return;

            _MapObj.ListEnemy.Clear();

            int mapHeight = _MapObj.MapRow * MapObject.ROW_SIZE;
            //list enemy here
            bool valid = true;
            while (!sr.EndOfStream)
            {
                #region ID
                do
                {
                    id = 0;
                    valid = false;
                    try
                    {
                        temp = sr.Read();
                    }
                    catch
                    {
                        sr.Close();
                        return;
                    }
                    while (temp > 47 && temp < 58)
                    {
                        id = id * 10 + (temp - 48);
                        valid = true;
                        try
                        {
                            temp = sr.Read();
                        }
                        catch
                        {
                            sr.Close();
                            return;
                        }
                    }
                } while (!sr.EndOfStream && !valid);
                #endregion

                #region X
                do
                {
                    x = 0;
                    valid = false;
                    try
                    {
                        temp = sr.Read();
                    }
                    catch
                    {
                        sr.Close();
                        return;
                    }
                    while (temp > 47 && temp < 58)
                    {
                        x = x * 10 + (temp - 48);
                        valid = true;
                        try
                        {
                            temp = sr.Read();
                        }
                        catch
                        {
                            sr.Close();
                            return;
                        }
                    }
                } while (!sr.EndOfStream && !valid);
                #endregion

                #region Y
                do
                {
                    y = 0;
                    valid = false;
                    try
                    {
                        temp = sr.Read();
                    }
                    catch
                    {
                        sr.Close();
                        return;
                    }
                    while (temp > 47 && temp < 58)
                    {
                        y = y * 10 + (temp - 48);
                        valid = true;
                        try
                        {
                            temp = sr.Read();
                        }
                        catch
                        {
                            sr.Close();
                            return;
                        }
                    }
                } while (!sr.EndOfStream && !valid);
                #endregion         

                #region NOTE
                string note = null;
                try
                {
                    note = sr.ReadLine();
                }
                catch
                {
                    sr.Close();
                    return;
                }
                #endregion

                try
                {
                    
                    if (id < 1)
                    { }
                    else if (id == 1)
                    {
                        int width;
                        if (int.TryParse(note.Trim(), out width))
                        {
                            TileObject tileObj = new TileObject(id,
                            new System.Drawing.Point(x, mapHeight - y),
                            new System.Drawing.Size(width, MapObject.MINIMUM_HEIGHT));
                            if (note != null)
                                tileObj.Note = note;
                            _MapObj.ListGround.Add(tileObj);
                        }
                    }
                    else
                    {
                        if (id < _ListPicbox.Count)
                        {
                            TileObject tileObj = new TileObject(id,
                            new System.Drawing.Point(x, mapHeight - y),
                            new System.Drawing.Size(_ListPicbox[id].Image.Width * 2, _ListPicbox[id].Image.Height * 2));
                            if (!string.IsNullOrEmpty(note) && note != "-1")
                                tileObj.Note = note;
                            _MapObj.ListEnemy.Add(tileObj);
                        }
                    }
                }
                catch
                { }
            }
            sr.Close();
        }

        //tao 1 hinh chu nhat xac dinh boi 2 diem
        private Rectangle GetRectBetweenPoints(Point p1, Point p2)
        {
            Rectangle rect = new Rectangle();
            rect.Location = new Point(Math.Min(Math.Abs(p1.X), Math.Abs(p2.X)), Math.Min(Math.Abs(p1.Y), Math.Abs(p2.Y)));
            rect.Size = new Size(Math.Abs(p1.X - p2.X), Math.Abs(p1.Y - p2.Y));

            return rect;
        }



        //su kien click picture box chua anh
        private void pictureBox_Click(object sender, EventArgs e)
        {
            PictureBox newPb = (PictureBox)sender;
            if (newPb != null && newPb != _SelectedPicbox)
            {
                _SelectedPicbox.BackColor = Color.Transparent;
                _SelectedPicbox = newPb;
                _SelectedPicbox.BackColor = SystemColors.MenuHighlight;
            }
        }

        //load background
        private void _btnLoadBG_Click(object sender, EventArgs e)
        {
            OpenFileDialog dgl = new OpenFileDialog();
            dgl.Filter = "Image Files (bmp, jpg, png)|*.bmp;*.jpg;*.png";
            dgl.Multiselect = false;
            if (dgl.ShowDialog() == DialogResult.OK)
            {
                Bitmap bmp = null;
                try
                {
                    bmp = new Bitmap(dgl.FileName);
                }
                catch
                {
                    MessageBox.Show("Không load được back ground");
                    return;
                }

                if (bmp != null)
                {
                    _MapObj.MapRow = bmp.Height / MapObject.ROW_SIZE;
                    _MapObj.MapColumn = bmp.Width / MapObject.COLUMN_SIZE;
                    InitBackground();
                    _pbBackground.Image = bmp;
                }
                else
                    MessageBox.Show("Không load được back ground");
            }
        }

        //ve lai pbBackground
        private void pbBackground_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            DrawLine(g);
            foreach (TileObject tileObj in _MapObj.ListEnemy)
            {
                Rectangle r = new Rectangle();
                r.Location = new Point(
                    tileObj.TilePoint.X - tileObj.TileSize.Width/2,
                    tileObj.TilePoint.Y - tileObj.TileSize.Height/2
                    );
                r.Size = tileObj.TileSize;
                try
                {
                    g.DrawImage(_ListPicbox[tileObj.Id].Image, r);
                }
                catch
                { }
            }

            Pen pen = new Pen(Color.Red, 3.0f);
            foreach (TileObject tileObj in _MapObj.ListGround)
            {
                Rectangle r = new Rectangle();
                r.Location = new Point(
                    tileObj.TilePoint.X - tileObj.TileSize.Width/2,
                    tileObj.TilePoint.Y - tileObj.TileSize.Height/2
                    );
                r.Size = tileObj.TileSize;
                try
                {
                    g.DrawRectangle(pen, r);
                }
                catch
                { }
            }
        }

        //mouse down pbBackground
        private void pbBackground_MouseDown(object sender, MouseEventArgs e)
        {
            _IsMouseDown = true;
            if (_SelectedObj != null)
                _SelectedObj = null;
            if (_SelectedPicbox == _pbEraser)
            {
                TileObject enemyObj = _MapObj.GetEnemyAtPoint(e.Location);
                if (enemyObj != null)
                    _MapObj.ListEnemy.Remove(enemyObj);

                TileObject groundObj = _MapObj.GetGroundAtPoint(e.Location);
                    if (groundObj != null)
                        _MapObj.ListGround.Remove(groundObj);
            }
            else if (_SelectedPicbox == _pbLand)
            {
                _startPoint = new Point(e.X / MapObject.MINIMUM_WIDTH * MapObject.MINIMUM_WIDTH,
                    e.Y / MapObject.MINIMUM_HEIGHT * MapObject.MINIMUM_HEIGHT);
            }
            else
            {
                int id = _ListPicbox.IndexOf(_SelectedPicbox);
                TileObject enemyObj = _MapObj.GetEnemyAtPoint(e.Location);
                if (enemyObj != null)
                {
                    if (enemyObj.Id != id)
                    {
                        enemyObj.Id = id;
                        enemyObj.TilePoint = new Point(e.Location.X, e.Location.Y);
                        enemyObj.TileSize = new Size(_SelectedPicbox.Image.Width * 2, _SelectedPicbox.Image.Height * 2);
                        _SelectedObj = enemyObj;
                        _txtNote.Text = _SelectedObj.Note;
                    }
                    else
                    {
                        _SelectedObj = enemyObj;
                        _txtNote.Text = _SelectedObj.Note;
                    }
                }
                else
                {
                    enemyObj = new TileObject(
                        id,
                        new Point(e.Location.X, e.Location.Y),
                        new Size(_SelectedPicbox.Image.Width * 2, _SelectedPicbox.Image.Height * 2)
                        );
                    _MapObj.ListEnemy.Add(enemyObj);
                    _SelectedObj = enemyObj;
                    _txtNote.Text = _SelectedObj.Note;
                }
            }

            if (_pbBackground != null)
                _pbBackground.Invalidate();
        }

        //mouse move pbBackground
        private void pbBackground_MouseMove(object sender, MouseEventArgs e)
        {
            //scroll truc x
            int limitX = e.X + _pbBackground.Left;
            if (limitX + 20 > _pnlDrawMap.Width)
            {
                if (_pnlDrawMap.HorizontalScroll.Value + 20 < _pnlDrawMap.HorizontalScroll.Maximum)
                    _pnlDrawMap.HorizontalScroll.Value += 20;
                else
                    _pnlDrawMap.HorizontalScroll.Value = _pnlDrawMap.HorizontalScroll.Maximum;
            }
            if (limitX - 20 < 0)
            {
                if (_pnlDrawMap.HorizontalScroll.Value - 20 > _pnlDrawMap.HorizontalScroll.Minimum)
                    _pnlDrawMap.HorizontalScroll.Value -= 20;
                else
                    _pnlDrawMap.HorizontalScroll.Value = _pnlDrawMap.HorizontalScroll.Minimum;
            }

            //scroll truc y
            int limitY = e.Y + _pbBackground.Top;
            if (limitY - 20 < 0)
            {
                if (_pnlDrawMap.VerticalScroll.Value - 20 < _pnlDrawMap.VerticalScroll.Minimum)
                    _pnlDrawMap.VerticalScroll.Value = _pnlDrawMap.VerticalScroll.Minimum;
                else
                    _pnlDrawMap.VerticalScroll.Value -= 20;
            }
            if (limitY + 20 > _pnlDrawMap.Height)
            {
                if (_pnlDrawMap.VerticalScroll.Value + 20 > _pnlDrawMap.VerticalScroll.Maximum)
                    _pnlDrawMap.VerticalScroll.Value = _pnlDrawMap.VerticalScroll.Maximum;
                else
                    _pnlDrawMap.VerticalScroll.Value += 20;
            }

            _txtCenterX.Text = e.Location.X.ToString();
            _txtCenterY.Text = (_MapObj.MapRow * MapObject.ROW_SIZE - e.Location.Y).ToString();

            if (_SelectedObj != null && _SelectedObj.Id != 0 && _SelectedObj.Id != 1)
            {
                _txtBotLeftX.Text = (_SelectedObj.TilePoint.X - _SelectedObj.TileSize.Width / 2).ToString();
                _txtBotLeftY.Text = (_MapObj.MapRow * MapObject.ROW_SIZE - _SelectedObj.TilePoint.Y - _SelectedObj.TileSize.Height / 2).ToString();
            }
            
            if (_IsMouseDown)
            {
                if (_SelectedPicbox == _pbEraser)
                { }
                else if (_SelectedPicbox == _pbLand)
                {
                    _endPoint = e.Location;
                }
                else
                {
                    if (_SelectedObj != null)
                    {
                        Point _point = new Point(e.Location.X, e.Location.Y);

                        if (_point.X < 0)
                            _point.X = 0;

                        if (_point.Y < 0)
                            _point.Y = 0;

                        _SelectedObj.TilePoint = _point;
                    }
                }
            }

            if (_pbBackground != null)
                _pbBackground.Invalidate();
        }

        //mouse up pbBackground
        private void pbBackground_MouseUp(object sender, MouseEventArgs e)
        {
            if (_SelectedPicbox == _pbEraser)
            { }
            else if (_SelectedPicbox == _pbLand)
            {
                _endPoint = new Point(e.X / MapObject.MINIMUM_WIDTH * MapObject.MINIMUM_WIDTH,
                                        e.Y / MapObject.MINIMUM_HEIGHT * MapObject.MINIMUM_HEIGHT);
                Rectangle rect = GetRectBetweenPoints(_startPoint, _endPoint);
                if (rect.Size.Height > 0 && rect.Size.Width > 0)
                {
                    TileObject tileObj = new TileObject(
                        _ListPicbox.IndexOf(_pbLand),
                        new Point(rect.Location.X + rect.Size.Width/2, rect.Location.Y + rect.Size.Height/2),
                        new Size(rect.Size.Width, MapObject.MINIMUM_HEIGHT));
                    _MapObj.ListGround.Add(tileObj);
                }
            }
            else
            { }

            _IsMouseDown = false;
            if (_pbBackground != null)
                _pbBackground.Invalidate();
        }

        //click button Clear
        private void _btnClear_Click(object sender, EventArgs e)
        {
            _MapObj.ListEnemy.Clear();
            _MapObj.ListGround.Clear();
            if (_pbBackground != null)
                _pbBackground.Invalidate();
        }

        //click button Exit
        private void _btnExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        //set bot left position for object
        private void _btnSetBotLeft_Click(object sender, EventArgs e)
        {
            if (_SelectedObj != null)
            {
                int x;
                int y;
                if (int.TryParse(_txtBotLeftX.Text, out x) && int.TryParse(_txtBotLeftY.Text, out y))
                {
                    _SelectedObj.TilePoint = new Point(x + _SelectedObj.TileSize.Width/2,
                        _MapObj.MapRow * MapObject.ROW_SIZE - y - _SelectedObj.TileSize.Height / 2);
                    _pbBackground.Invalidate();
                    MessageBox.Show("Success!");
                }
            }
            else
                MessageBox.Show("Please select a object to set bot left position");
        }

        //set center position for object
        private void _btnSetCenter_Click(object sender, EventArgs e)
        {
            if (_SelectedObj != null)
            {
                int x;
                int y;
                if (int.TryParse(_txtCenterX.Text, out x) && int.TryParse(_txtCenterY.Text, out y))
                {
                    _SelectedObj.TilePoint = new Point(x, _MapObj.MapRow * MapObject.ROW_SIZE - y);
                    _pbBackground.Invalidate();
                    MessageBox.Show("Success!");
                }
            }
            else
                MessageBox.Show("Please select a object to set center position");
        }

        //set note for object
        private void _btnSetNote_Click(object sender, EventArgs e)
        {
            if (_SelectedObj != null)
            {
                if (_SelectedObj.Id == 1)
                    MessageBox.Show("Can not set note for object Ground");
                else
                {
                    _SelectedObj.Note = _txtNote.Text;
                    MessageBox.Show("Success!");
                }
            }
            else
                MessageBox.Show("Please select a object to set note");
        }

        //click button Save
        private void _btnSaveMap_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Filter = "map files (*.txt)|*.txt";
            dlg.Title = "Save map";
            dlg.CheckPathExists = true;
            dlg.ShowDialog();

            if (WriteFile(dlg.FileName))
                MessageBox.Show("Lưu thành công");
            else
                MessageBox.Show("Lưu thất bại");

        }

        //click button Load
        private void _btnLoadMap_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "Map Files (txt)|*.txt";
            dlg.Multiselect = false;
            if (dlg.ShowDialog() == DialogResult.OK)
                ReadFile(dlg.FileName);
            if (_pbBackground != null)
                _pbBackground.Invalidate();
        }
    }
}
