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

        //quadtree
        private Node _QuadTree;

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
            _QuadTree = null;
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
            _MapObj.ListObject.Clear();

            _pbBackground = new PictureBox();
            _pbBackground.Width = _MapObj.MapWidth;
            _pbBackground.Height = _MapObj.MapHeight;
            _pbBackground.Paint += pbBackground_Paint;

            _pbBackground.MouseDown += pbBackground_MouseDown;
            _pbBackground.MouseUp += pbBackground_MouseUp;
            _pbBackground.MouseMove += pbBackground_MouseMove;

            _pnlDrawMap.Controls.Add(_pbBackground);
        }

        //build quadtree
        private void BuildQuadTree()
        {
            //calculate width, height
            int width = (_MapObj.MapWidth / Node.SCREEN_WIDTH + 1) * Node.SCREEN_WIDTH;
            int height = width;
            //create node root
            _QuadTree = new Node(0, REGION.TOP_LEFT, new Box(width/2, height/2, width, height));
            //add objects to node
            foreach (TileObject obj in _MapObj.ListGround)
                Node.InsertNode(_QuadTree, obj);
            foreach (TileObject obj in _MapObj.ListObject)
                Node.InsertNode(_QuadTree, obj);
        }

        //khoi tao danh sach picture box chua anh cua enemy
        private void InitListPb()
        {
            _ListPicbox = new List<PictureBox>();
            _ListPicbox.Add(_pbEraser);//0
            _ListPicbox.Add(_pbLand);//1
            _ListPicbox.Add(_pbTile1);//2
            _ListPicbox.Add(_pbTile2);//3
            _ListPicbox.Add(_pbTile3);//4
            _ListPicbox.Add(_pbTile4);//5
            _ListPicbox.Add(_pbTile5);//6
            _ListPicbox.Add(_pbTile6);//7
            _ListPicbox.Add(_pbTile7);//8
            _ListPicbox.Add(_pbTile8);//9
            _ListPicbox.Add(_pbTile9);//10
            _ListPicbox.Add(_pbTile10);//11
            _ListPicbox.Add(_pbTile11);//12
            _ListPicbox.Add(_pbTile12);//13
            _ListPicbox.Add(_pbTile13);//14
            _ListPicbox.Add(_pbItem1);//15
            _ListPicbox.Add(_pbItem2);//16
            _ListPicbox.Add(_pbItem3);//17
            _ListPicbox.Add(_pbItem4);//18
            _ListPicbox.Add(_pbItem5);//19
            _ListPicbox.Add(_pbItem6);//20
            _ListPicbox.Add(_pbItem7);//21
            _ListPicbox.Add(_pbItem8);//22
            _ListPicbox.Add(_pbItem9);//23
            _ListPicbox.Add(_pbEnemy1);//24
            _ListPicbox.Add(_pbEnemy2);//25
            _ListPicbox.Add(_pbEnemy3);//26
            _ListPicbox.Add(_pbEnemy4);//27
            _ListPicbox.Add(_pbEnemy5);//28
            _ListPicbox.Add(_pbEnemy6);//29
            _ListPicbox.Add(_pbEnemy7);//30
            _ListPicbox.Add(_pbEnemy8);//31
            _ListPicbox.Add(_pbTile14);//32
            _ListPicbox.Add(_pbTile15);//33
            _ListPicbox.Add(_pbItem10);//34
            _ListPicbox.Add(_pbItem11);//35
            _ListPicbox.Add(_pbEnemy9);//36
            _ListPicbox.Add(_pbEnemy10);//37
            _ListPicbox.Add(_pbLava);   //38
            _ListPicbox.Add(_pbTile16); //39
            _ListPicbox.Add(_pbTile17); //40
            _ListPicbox.Add(_pbEnemy11);//41
            _ListPicbox.Add(_pbEnemy12);//42
            _ListPicbox.Add(_pbMushroomRetainer);//43
            _ListPicbox.Add(_pbPrincess);//44

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
                sw = new System.IO.StreamWriter(path, false);
            }
            catch
            {
                return false;
            }

            try
            {
                foreach (TileObject tileObj in _MapObj.ListGround)
                    sw.WriteLine(
                        tileObj.Id.ToString() + " "
                         + tileObj.BoundaryBox.X.ToString() + " "
                         + tileObj.BoundaryBox.Y.ToString() + " "
                         + tileObj.BoundaryBox.Width.ToString() + " "
                         + tileObj.BoundaryBox.Height.ToString() + " "
                         + "-1"
                         );

                foreach (TileObject tileObj in _MapObj.ListObject)
                {
                    if (string.IsNullOrEmpty(tileObj.Note))
                        sw.WriteLine(
                            tileObj.Id.ToString() + " "
                             + tileObj.BoundaryBox.X.ToString() + " "
                             + tileObj.BoundaryBox.Y.ToString() + " "
                             + tileObj.BoundaryBox.Width.ToString() + " "
                             + tileObj.BoundaryBox.Height.ToString() + " "
                             + "-1"
                             );
                    else
                        sw.WriteLine(
                            tileObj.Id.ToString() + " "
                             + tileObj.BoundaryBox.X.ToString() + " "
                             + tileObj.BoundaryBox.Y.ToString() + " "
                             + tileObj.BoundaryBox.Width.ToString() + " "
                             + tileObj.BoundaryBox.Height.ToString() + " "
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

        //write node
        private void WriteNode(Node node, StreamWriter sw)
        {
            if (node != null)
            {
                //write node info
                sw.WriteLine(node.NodeId + " " + node.BoundaryBox.X + " " + node.BoundaryBox.Y + " "
                    + node.BoundaryBox.Width + " " + node.BoundaryBox.Height + " " + node.ListObject.Count);
                //write objects in node
                if (node.ListObject.Count > 0)
                {
                    node.ListObject.Sort();
                    foreach (TileObject obj in node.ListObject)
                    {
                        switch (obj.Id)
                        {
                            case (int)eOBJECTID.COLUMN_FIRE:
                                {
                                    if (string.IsNullOrEmpty(obj.Note))
                                        sw.WriteLine(
                                            obj.Id.ToString() + " "
                                                + obj.MovementRangeBox.X.ToString() + " "
                                                + (obj.MovementRangeBox.Y + obj.MovementRangeBox.Height/2).ToString() + " "
                                                + obj.MovementRangeBox.Width.ToString() + " "
                                                + obj.MovementRangeBox.Height.ToString() + " "
                                                + "0"
                                                );
                                    else
                                        sw.WriteLine(
                                            obj.Id.ToString() + " "
                                                + obj.MovementRangeBox.X.ToString() + " "
                                                + (obj.MovementRangeBox.Y + obj.MovementRangeBox.Height / 2).ToString() + " "
                                                + obj.MovementRangeBox.Width.ToString() + " "
                                                + obj.MovementRangeBox.Height.ToString() + " "
                                                + obj.Note
                                                );
                                    break;
                                }
                            case (int)eOBJECTID.FLAG:
                                {
                                    if (string.IsNullOrEmpty(obj.Note))
                                        sw.WriteLine(
                                            obj.Id.ToString() + " "
                                                + (obj.MovementRangeBox.X + 12).ToString() + " "
                                                + obj.MovementRangeBox.Y.ToString() + " "
                                                + TileObject.FLAG_WIDTH + " "
                                                + obj.MovementRangeBox.Height.ToString() + " "
                                                + "-1"
                                                );
                                    else
                                        sw.WriteLine(
                                            obj.Id.ToString() + " "
                                                + (obj.MovementRangeBox.X + 12).ToString() + " "
                                                + obj.MovementRangeBox.Y.ToString() + " "
                                                + TileObject.FLAG_WIDTH + " "
                                                + obj.MovementRangeBox.Height.ToString() + " "
                                                + obj.Note
                                                );
                                    break;
                                }
                            default:
                                {
                                    if (string.IsNullOrEmpty(obj.Note))
                                        sw.WriteLine(
                                            obj.Id.ToString() + " "
                                                + obj.MovementRangeBox.X.ToString() + " "
                                                + obj.MovementRangeBox.Y.ToString() + " "
                                                + obj.MovementRangeBox.Width.ToString() + " "
                                                + obj.MovementRangeBox.Height.ToString() + " "
                                                + "-1"
                                                );
                                    else
                                        sw.WriteLine(
                                            obj.Id.ToString() + " "
                                                + obj.MovementRangeBox.X.ToString() + " "
                                                + obj.MovementRangeBox.Y.ToString() + " "
                                                + obj.MovementRangeBox.Width.ToString() + " "
                                                + obj.MovementRangeBox.Height.ToString() + " "
                                                + obj.Note
                                                );
                                    break;
                                }
                        }
                    }
                }
                //write subnodes
                WriteNode(node.Tl, sw);
                WriteNode(node.Tr, sw);
                WriteNode(node.Bl, sw);
                WriteNode(node.Br, sw);
            }
        }

        //write quadtree
        private bool WriteQuadTree(string path)
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

            try
            {
                WriteNode(_QuadTree, sw);
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
            int w = 0;
            int h = 0;

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

            _MapObj.ListObject.Clear();

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

                #region Width
                do
                {
                    w = 0;
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
                        w = w * 10 + (temp - 48);
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

                #region Height
                do
                {
                    h = 0;
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
                        h = h * 10 + (temp - 48);
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
                    else if (id == (int)eOBJECTID.GROUND || id == (int)eOBJECTID.LAVA)
                    {
                        TileObject tileObj = new TileObject(id, x, y, w, h);
                        if (note != null)
                            tileObj.Note = note;
                        _MapObj.ListGround.Add(tileObj);
                    }                    
                    else
                    {
                        if (id < _ListPicbox.Count)
                        {
                            TileObject tileObj = new TileObject(id, x, y, w, h);
                            if (!string.IsNullOrEmpty(note) && note != "-1")
                                tileObj.Note = note;
                            _MapObj.ListObject.Add(tileObj);
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
                    _MapObj.MapWidth = bmp.Width;
                    _MapObj.MapHeight = bmp.Height;
                    _MapObj.MapColumn = _MapObj.MapWidth / MapObject.COLUMN_SIZE;
                    _MapObj.MapRow = _MapObj.MapHeight / MapObject.ROW_SIZE;
                    InitBackground();
                    _pbBackground.Image = bmp;
                    if (_QuadTree != null)
                        _QuadTree = null;
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
            foreach (TileObject tileObj in _MapObj.ListObject)
            {
                Rectangle r = new Rectangle();
                r.Location = new Point(
                    tileObj.BoundaryBox.X - tileObj.BoundaryBox.Width/2,
                    _MapObj.MapHeight - (tileObj.BoundaryBox.Y + tileObj.BoundaryBox.Height/2)
                    );
                r.Size = new Size(tileObj.BoundaryBox.Width, tileObj.BoundaryBox.Height);
                try
                {
                    g.DrawImage(_ListPicbox[tileObj.Id].Image, r);
                }
                catch
                { }
            }

            Pen browmPen = new Pen(Color.Yellow, 3.0f);
            Pen redPen = new Pen(Color.Red, 3.0f);
            foreach (TileObject tileObj in _MapObj.ListGround)
            {
                Rectangle r = new Rectangle();
                r.Location = new Point(
                    tileObj.BoundaryBox.X - tileObj.BoundaryBox.Width/2,
                    _MapObj.MapHeight - (tileObj.BoundaryBox.Y + tileObj.BoundaryBox.Height / 2)
                    );
                r.Size = new Size(tileObj.BoundaryBox.Width, tileObj.BoundaryBox.Height);
                try
                {
                    switch(tileObj.Id)
                    {
                        case (int)eOBJECTID.GROUND:
                            g.DrawRectangle(browmPen, r);
                            break;
                        case (int)eOBJECTID.LAVA:
                            g.DrawRectangle(redPen, r);
                            break;
                    }
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
                TileObject enemyObj = _MapObj.GetObjectAtPoint(e.Location.X, _MapObj.MapHeight - e.Location.Y);
                if (enemyObj != null)
                    _MapObj.ListObject.Remove(enemyObj);

                TileObject groundObj = _MapObj.GetGroundAtPoint(e.Location.X, _MapObj.MapHeight - e.Location.Y);
                    if (groundObj != null)
                        _MapObj.ListGround.Remove(groundObj);
            }
            else if (_SelectedPicbox == _pbLand || _SelectedPicbox == _pbLava)
            {
                _startPoint = new Point(e.X / MapObject.MINIMUM_WIDTH * MapObject.MINIMUM_WIDTH,
                    e.Y / MapObject.MINIMUM_HEIGHT * MapObject.MINIMUM_HEIGHT);
            }
            else
            {
                int id = _ListPicbox.IndexOf(_SelectedPicbox);
                int x = e.Location.X;
                int y = _MapObj.MapHeight - e.Location.Y;
                TileObject enemyObj = _MapObj.GetObjectAtPoint(x, y);
                if (enemyObj != null)
                {
                    if (enemyObj.Id != id)
                    {
                        enemyObj.Id = id;
                        enemyObj.BoundaryBox.Width = _SelectedPicbox.Image.Width * 2;
                        enemyObj.BoundaryBox.Height = _SelectedPicbox.Image.Height * 2;
                        if (enemyObj.BoundaryBox.Width == MapObject.COLUMN_SIZE
                            && enemyObj.BoundaryBox.Height == MapObject.ROW_SIZE)
                        {
                            enemyObj.BoundaryBox.X = (x / MapObject.COLUMN_SIZE) * MapObject.COLUMN_SIZE + MapObject.COLUMN_SIZE / 2;
                            enemyObj.BoundaryBox.Y = (y / MapObject.ROW_SIZE) * MapObject.ROW_SIZE + MapObject.ROW_SIZE / 2;
                        }
                        
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
                    if (_SelectedPicbox.Image.Width * 2 == MapObject.COLUMN_SIZE
                            && _SelectedPicbox.Image.Width * 2 == MapObject.ROW_SIZE)
                    {
                        enemyObj = new TileObject(
                            id,
                            (x / MapObject.COLUMN_SIZE) * MapObject.COLUMN_SIZE + MapObject.COLUMN_SIZE / 2,
                            (y / MapObject.ROW_SIZE) * MapObject.ROW_SIZE + MapObject.ROW_SIZE / 2,
                            _SelectedPicbox.Image.Width * 2,
                            _SelectedPicbox.Image.Height * 2
                            );
                    }
                    else
                    {
                        enemyObj = new TileObject(id, x, y,
                            _SelectedPicbox.Image.Width * 2,
                            _SelectedPicbox.Image.Height * 2
                            );
                    }
                    _MapObj.ListObject.Add(enemyObj);
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
            _txtCenterY.Text = (_MapObj.MapHeight - e.Location.Y).ToString();

            if (_SelectedObj != null && _SelectedObj.Id != 0 && _SelectedObj.Id != 1)
            {
                _txtBotLeftX.Text = (_SelectedObj.BoundaryBox.X - _SelectedObj.BoundaryBox.Width / 2).ToString();
                _txtBotLeftY.Text = (_SelectedObj.BoundaryBox.Y - _SelectedObj.BoundaryBox.Height / 2).ToString();
            }
            
            if (_IsMouseDown)
            {
                if (_SelectedPicbox == _pbEraser)
                { }
                else if (_SelectedPicbox == _pbLand || _SelectedPicbox == _pbLava)
                {
                    _endPoint = e.Location;
                }
                else
                {
                    if (_SelectedObj != null)
                    {
                        _SelectedObj.BoundaryBox.X = e.Location.X;
                        _SelectedObj.BoundaryBox.Y = _MapObj.MapHeight - e.Location.Y;
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
                        rect.Location.X + rect.Size.Width/2,
                        _MapObj.MapHeight - (rect.Location.Y + rect.Size.Height/2),
                        rect.Size.Width,
                        rect.Size.Height
                        );
                    _MapObj.ListGround.Add(tileObj);
                }
            }
            else if (_SelectedPicbox == _pbLava)
            {
                _endPoint = new Point(e.X / MapObject.MINIMUM_WIDTH * MapObject.MINIMUM_WIDTH,
                                        e.Y / MapObject.MINIMUM_HEIGHT * MapObject.MINIMUM_HEIGHT);
                Rectangle rect = GetRectBetweenPoints(_startPoint, _endPoint);
                if (rect.Size.Height > 0 && rect.Size.Width > 0)
                {
                    TileObject tileObj = new TileObject(
                        _ListPicbox.IndexOf(_pbLava),
                        rect.Location.X + rect.Size.Width / 2,
                        _MapObj.MapHeight - (rect.Location.Y + rect.Size.Height / 2),
                        rect.Size.Width,
                        MapObject.MINIMUM_HEIGHT
                        );
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
            _MapObj.ListObject.Clear();
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
                    _SelectedObj.BoundaryBox.X = x + _SelectedObj.BoundaryBox.Width/2;
                    _SelectedObj.BoundaryBox.Y = y + _SelectedObj.BoundaryBox.Height/2;
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
                    _SelectedObj.BoundaryBox.X = x;
                    _SelectedObj.BoundaryBox.Y = y;
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
                if (_SelectedObj.Id == (int)eOBJECTID.GROUND)
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

            BuildQuadTree();

            if (WriteFile(dlg.FileName) && WriteQuadTree(dlg.FileName.Replace(".txt", "_quadtree.txt")))
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
