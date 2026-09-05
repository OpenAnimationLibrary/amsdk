"""Real Tk/Pillow frontend tests. Fake acknowledgements do NOT test A:M mutation."""
from pathlib import Path
import sys, tempfile, time, unittest, hashlib
from types import SimpleNamespace
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'runtime'))
from PIL import Image
from patch_draw_studio import StudioApp
from studio_core import Drawing, Session, atomic_json, strict_json

class UITests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temp=tempfile.TemporaryDirectory(prefix='studio-ui-')
        cls.root=Path(cls.temp.name)
        cls.app=StudioApp(Session(cls.root)); cls.errors=[]
        cls.app.report_callback_exception=lambda *args: cls.errors.append(str(args))
        cls.app.update()
    @classmethod
    def tearDownClass(cls):
        cls.app.destroy(); cls.temp.cleanup()
    def setUp(self):
        a=self.app
        a.finish_paint_strokes(); a.draw_canvas.cancel()
        a.session=Session(self.root); a.pending=0; a.connected=False
        a.drawing=Drawing(side=4,cells={(x,y) for x in range(4) for y in range(4)})
        a.image=Image.new('RGB',(256,256),(210,210,210)); a.erase_baseline=a.image.copy()
        a.undo_stack.clear(); a.redo_stack.clear(); a.geometry_undo.clear(); a.geometry_redo.clear()
        a.paint_color.set('#ff0000'); a.opacity.set(100); a.brush_size.set(12)
        a.live_preview.set(True); a.include_paint.set(True); a.patch_only.set(True)
        a.update_fields(); a.tabs.select(0); a.rebuild(); a.update()
    def tearDown(self):
        self.assertEqual(self.errors,[])
    def pixel_hash(self): return hashlib.sha256(self.app.image.tobytes()).hexdigest()
    def heartbeat(self,**extra):
        a=self.app
        atomic_json(a.session.path/'receiver.json',dict(session=a.session.token,status='connected',target='Test Model',updated=int(time.time()*1000),**extra))
        a.poll_receiver()
    def test_01_draw_cancel_release_and_separate_undo(self):
        a=self.app; a.drawing.cells.clear(); a.rebuild(); c=a.draw_canvas
        scale,x,y=c.geometry_values(); e=SimpleNamespace(x=x+scale*.5,y=y-scale*.5,state=0x100)
        c.down(e); self.assertIsNotNone(c.before); self.assertTrue(a.drawing.cells)
        c.cancel(); self.assertEqual(a.drawing.cells,set())
        c.down(e); c.up(e); drawn=set(a.drawing.cells); self.assertTrue(drawn)
        a.geometry_back(); self.assertEqual(a.drawing.cells,set())
        a.geometry_forward(); self.assertEqual(a.drawing.cells,drawn)
        c.down(e); c.move(SimpleNamespace(x=e.x,y=e.y,state=0)); self.assertIsNone(c.before)
        self.assertEqual(a.drawing.cells,drawn)
    def test_02_fill_erase_undo_redo_and_patch_masks(self):
        a=self.app; before=self.pixel_hash(); a.set_selected_patch(0); a.fill_selected_patch(); after=self.pixel_hash()
        self.assertNotEqual(before,after); a.undo(); self.assertEqual(before,self.pixel_hash())
        a.redo(); self.assertEqual(after,self.pixel_hash())
        p=a.model.patches[0]; u0,v0,u1,v1=p.uv_bounds; x=(u0+u1)*128; y=(v0+v1)*128
        a.begin_edit(); a.paint_segment(x,y,x,y,erase=True); a.finish_edit()
        self.assertEqual(a.image.getpixel((round(x),round(y))),(210,210,210))
        for i in range(12): a.get_patch_mask(i)
        self.assertLessEqual(len(a.patch_masks),4)
    def test_03_save_load_draft_and_reject_damage(self):
        a=self.app; a.shape_name.set('Saved Bridge'); a.fields['surface'].set('Arch X'); a.apply_settings()
        a.set_selected_patch(0); a.fill_selected_patch(); expected=self.pixel_hash(); saved=a.drawing.recipe()
        dest=self.root/'roundtrip.patchdraw'
        with patch('patch_draw_studio.filedialog.asksaveasfilename',return_value=str(dest)):
            self.assertTrue(a.save_project())
        a.drawing.cells.clear(); a.image.paste((0,0,0),(0,0,256,256))
        with patch.object(a,'confirm_discard_changes',return_value=True), patch('patch_draw_studio.filedialog.askopenfilename',return_value=str(dest)):
            a.open_project()
        self.assertEqual(a.drawing.recipe(),saved); self.assertEqual(self.pixel_hash(),expected)
        bad=self.root/'bad.patchdraw'; bad.write_bytes(b'not a zip')
        with patch.object(a,'confirm_discard_changes',return_value=True), patch('patch_draw_studio.filedialog.askopenfilename',return_value=str(bad)), patch('patch_draw_studio.messagebox.showerror') as error:
            a.open_project(); self.assertTrue(error.called)
        self.assertEqual(a.drawing.recipe(),saved)
    def test_04_refine_preserves_world_and_paint(self):
        a=self.app; a.set_selected_patch(0); a.fill_selected_patch(); old=self.pixel_hash()
        a.refine(); self.assertEqual(a.drawing.side,8); self.assertEqual(a.drawing.width,100)
        self.assertEqual(self.pixel_hash(),old); self.assertEqual(len(a.mesh['faces']),256)
    def test_05_send_is_snapshot_not_live_replacement(self):
        a=self.app; self.heartbeat(); self.assertTrue(a.connected)
        a.send_snapshot(); self.assertEqual(a.pending,1); self.assertTrue(a.winfo_exists())
        request=a.session.path/'request.json'; first=request.read_bytes(); plan=strict_json(first.decode())
        png=a.session.path/plan['texture']; pixels=png.read_bytes()
        a.image.paste((10,20,30),(0,0,256,256)); a.shape_name.set('Later Shape'); a.apply_settings(); a.send_snapshot()
        self.assertEqual(request.read_bytes(),first); self.assertEqual(png.read_bytes(),pixels)
        atomic_json(a.session.path/'result.json',dict(session='0'*32,serial=1,status='ok',message='wrong session'))
        a.poll_receiver(); self.assertEqual(a.pending,1)
        atomic_json(a.session.path/'result.json',dict(session=a.session.token,serial=True,status='ok',message='bad serial'))
        a.poll_receiver(); self.assertEqual(a.pending,1)
        request.rename(a.session.path/'processed-1.json')
        atomic_json(a.session.path/'result.json',dict(session=a.session.token,serial=1,status='ok',message='PD_Shape_001'))
        a.poll_receiver(); self.assertEqual(a.pending,0)
        a.send_snapshot(); self.assertEqual(a.pending,2); self.assertEqual(png.read_bytes(),pixels)
        second=strict_json(request.read_text()); self.assertNotEqual(plan['texture'],second['texture'])
        self.assertEqual(second['name'],'Later Shape'); self.assertTrue(a.winfo_exists())
    def test_06_ambiguous_send_never_overwritten(self):
        a=self.app; self.heartbeat(); marker=a.session.path/'processing.json'; marker.write_text('{}')
        with patch('patch_draw_studio.messagebox.showerror') as error: a.send_snapshot(); self.assertTrue(error.called)
        self.assertEqual(marker.read_text(),'{}'); self.assertFalse((a.session.path/'request.json').exists())
    def test_07_large_grid_disables_stale_projected_picking(self):
        a=self.app; a.drawing=Drawing(side=64,cells={(x,y) for x in range(64) for y in range(64)})
        a.update_fields(); a.rebuild(); self.assertFalse(a.live_preview.get()); self.assertEqual(len(a.mesh['faces']),16384)
        a.model_canvas._screen_polygons={999999:[(0,0),(20,0),(20,20),(0,20)]}
        a.model_canvas._right_press(SimpleNamespace(x=10,y=10)); self.assertIsNone(a.selected_patch)
        a.model_canvas._left_press(SimpleNamespace(x=10,y=10)); self.assertFalse(a.model_canvas._editing)
    def test_08_history_budget_and_minimum_layout(self):
        a=self.app; a.image=Image.new('RGB',(2048,2048)); a.erase_baseline=a.image.copy()
        for _ in range(5): a.begin_edit(); a.finish_edit()
        self.assertLessEqual(len(a.undo_stack),3)
        a.geometry('1060x660'); a.update()
        for widget in (a.send_button,a.footer):
            self.assertGreater(widget.winfo_width(),1)
            self.assertLessEqual(widget.winfo_rooty()+widget.winfo_height(),a.winfo_rooty()+a.winfo_height())
        a.geometry('1280x820'); a.update()
    def test_09_paint_focus_loss_finishes_one_undo_step(self):
        a=self.app; a.tabs.select(1); a.update(); c=a.texture_canvas; c.fit_image(); a.update()
        a.tool.set('brush'); x,y=c.image_to_canvas(16,240)
        c._left_press(SimpleNamespace(x=x,y=y,state=0x100)); self.assertIsNotNone(c._stroke_last)
        c._left_release(None); self.assertIsNone(c._stroke_last); self.assertEqual(len(a.undo_stack),1)
        a.undo(); self.assertEqual(a.image.tobytes(),a.erase_baseline.tobytes())
    def test_10_invalid_settings_do_not_replace_draft(self):
        a=self.app; old=a.drawing.recipe(); a.fields['origin'].set('nan,0,0')
        with patch('patch_draw_studio.messagebox.showerror') as error: self.assertFalse(a.apply_settings()); self.assertTrue(error.called)
        self.assertEqual(a.drawing.recipe(),old)

if __name__=='__main__':unittest.main(verbosity=2)
