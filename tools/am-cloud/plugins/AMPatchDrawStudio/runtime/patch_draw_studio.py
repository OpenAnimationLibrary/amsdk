"""Persistent Patch Draw / QuickDecal Painter frontend. No A:M SDK in this process.

QuickDecal Painter 1.1 source is bundled with one depth-sort extension hook. Its texture/model
canvases and painting methods are reused, with bounded masks/history, generated
UVs, safe draft persistence, and explicit snapshot sends added by this adapter.
"""
from __future__ import annotations
import argparse
import hashlib
from collections import deque
from copy import deepcopy
import io
import json
import os
from pathlib import Path
import sys
import time
import tkinter as tk
from tkinter import ttk, filedialog, messagebox
import zipfile

VENDOR=Path(__file__).resolve().parent / "quickdecal-1.1-studio.zip"
if not VENDOR.is_file() or hashlib.sha256(VENDOR.read_bytes()).hexdigest() != "0c6050462a9a64cbda0b52f35354bcd8ba4285ac797005e3663d3ff99f8d4051":
    raise SystemExit("Bundled QuickDecal source is missing or changed. Verify/extract the complete Studio package.")
sys.path.insert(0,str(VENDOR))
try:
    from PIL import Image, ImageDraw, ImageTk
    from am_bake import BakeModel, ControlPoint, Patch
    from quickdecal_painter import PainterApp, TextureCanvas, ModelCanvas
except ImportError as exc:
    raise SystemExit("Patch Draw Studio needs Tkinter and Pillow. Run Install_Dependencies.cmd with your chosen Python. " + str(exc))
from studio_core import Drawing, Session, SURFACES, compile_surface, sweep, atomic_json, strict_json, MAX_BYTES


class DrawCanvas(tk.Canvas):
    def __init__(self, parent, app):
        super().__init__(parent, background="#25292d", highlightthickness=0, cursor="crosshair")
        self.app=app; self.zoom=1.0; self.pan=[0.,0.]; self.before=None; self.last=None; self.redraw_job=None
        self.bind("<Configure>", self.configure_canvas)
        self.bind("<Button-1>",self.down); self.bind("<B1-Motion>",self.move); self.bind("<ButtonRelease-1>",self.up)
        self.bind("<Escape>",lambda e:self.cancel()); self.bind("<FocusOut>",lambda e:self.cancel())
        self.bind("<MouseWheel>",self.wheel)
        self.bind("<Button-4>",lambda e:self.wheel(e,1)); self.bind("<Button-5>",lambda e:self.wheel(e,-1))
        self.bind("<Button-2>",self.pan_start); self.bind("<B2-Motion>",self.pan_move)
        self.bind("<ButtonRelease-2>",lambda e:None)
    def configure_canvas(self,event):
        self.cancel(); self.redraw()
    def geometry_values(self):
        n=self.app.drawing.side
        scale=max(1,min(max(32,self.winfo_width()-30),max(32,self.winfo_height()-30))/n)*self.zoom
        return scale,(self.winfo_width()-n*scale)/2+self.pan[0],(self.winfo_height()+n*scale)/2+self.pan[1]
    def position(self,event):
        s,x,y=self.geometry_values(); return ((event.x-x)/s,(y-event.y)/s)
    def fit(self):
        self.zoom=1; self.pan=[0.,0.]; self.redraw()
    def wheel(self,event,step=None):
        if self.before is not None: return
        self.zoom=max(.5,min(8,self.zoom*(1.2 if (step or event.delta)>0 else 1/1.2))); self.redraw()
    def pan_start(self,event):
        self.cancel(); self.panning=(event.x,event.y,*self.pan)
    def pan_move(self,event):
        if hasattr(self,"panning"):
            x,y,px,py=self.panning; self.pan=[px+event.x-x,py+event.y-y]; self.redraw()
    def down(self,event):
        p=self.position(event); n=self.app.drawing.side
        if not(0<=p[0]<n and 0<=p[1]<n): return
        self.focus_set(); self.before=set(self.app.drawing.cells); self.last=p
        try:
            self.grab_set(); self.apply(p); self.after(80,self.check_capture)
        except (tk.TclError,ValueError) as exc:
            self.cancel(); self.app.status.set(str(exc))
    def check_capture(self):
        if self.before is not None:
            if self.grab_current() is not self: self.cancel()
            else: self.after(80,self.check_capture)
    def apply(self,p):
        sweep(self.app.drawing,self.last,p,float(self.app.draw_brush.get())/2,self.app.draw_tool.get()=="Erase")
        self.last=p
        if self.redraw_job is None: self.redraw_job=self.after(16,self.redraw)
    def move(self,event):
        if self.before is not None:
            if not(event.state & 0x100): self.cancel(); return
            try: self.apply(self.position(event))
            except ValueError as exc: self.cancel(); self.app.status.set(str(exc))
    def up(self,event):
        if self.before is None: return
        try: self.apply(self.position(event))
        except (ValueError,tk.TclError) as exc:
            self.cancel(); self.app.status.set(str(exc)); return
        old=self.before; self.before=None
        if self.grab_current() is self: self.grab_release()
        if old!=self.app.drawing.cells:
            self.app.geometry_undo.append(old); self.app.geometry_redo.clear(); self.app.draft_dirty=True
        self.app.rebuild(); self.redraw()
    def cancel(self):
        if self.before is not None:
            self.app.drawing.cells=self.before; self.before=None; self.last=None
            if self.grab_current() is self: self.grab_release()
            self.redraw(); self.app.status.set("Unfinished drawing stroke cancelled")
    def redraw(self):
        if self.redraw_job is not None:
            self.after_cancel(self.redraw_job); self.redraw_job=None
        self.delete("all"); s,ox,oy=self.geometry_values(); n=self.app.drawing.side
        self.create_rectangle(ox,oy-n*s,ox+n*s,oy,fill="#faf8f0",outline="#727e89")
        for x,y in self.app.drawing.cells:
            self.create_rectangle(ox+x*s,oy-(y+1)*s,ox+(x+1)*s,oy-y*s,fill="#619ca5",outline="")
        if s>=6:
            for i in range(n+1):
                self.create_line(ox+i*s,oy,ox+i*s,oy-n*s,fill="#9cacb0")
                self.create_line(ox,oy-i*s,ox+n*s,oy-i*s,fill="#9cacb0")
        self.create_text(12,12,anchor="nw",fill="#ffffff",text="Draft coverage | wheel: zoom | middle drag: pan | Esc: cancel stroke")


class StudioBakeModel(BakeModel):
    def patch_at_uv(self,u,v):
        if not(0<=u<=1 and 0<=v<=1): return None
        n=self.grid_side*2
        return self.cell_index.get((min(n-1,int(u*n)),min(n-1,int((1-v)*n))))


class StudioTextureCanvas(TextureCanvas):
    def __init__(self,parent,app):
        super().__init__(parent,app)
        self.bind("<FocusOut>",self._left_release)
    def _left_drag(self,event):
        if not(event.state & 0x100): self._left_release(event); return
        super()._left_drag(event)


class StudioModelCanvas(ModelCanvas):
    def __init__(self,parent,app):
        super().__init__(parent,app)
        self.bind("<FocusOut>",self._left_release)
    def _depth_key(self,patch):
        x,y,z=patch.centroid; view=self.app.projection.get()
        if view=="Oblique": return .5*x-.6*y+.866*z
        return z if view=="Front (X-Y)" else -y if view=="Top (Z-X)" else x
    def _right_press(self,event):
        if self.app.live_preview.get(): super()._right_press(event)
    def _motion(self,event):
        if self.app.live_preview.get(): super()._motion(event)
    def _project(self,p):
        if self.app.projection.get()=="Oblique":
            x,y,z=p; return (.866*x-.5*z, y+.3*x+.52*z)
        return super()._project(p)
    def _left_press(self,event):
        if not self.app.live_preview.get():
            self.app.status.set("Preview paused: paint in the texture view, or enable Live for projected painting."); return
        super()._left_press(event)
    def _left_drag(self,event):
        if not(event.state & 0x100): self._left_release(event); return
        if self.app.live_preview.get(): super()._left_drag(event)
    def render_now(self):
        super().redraw()
    def redraw(self):
        if self.app.live_preview.get(): super().redraw()
        elif self._redraw_job is not None:
            self.after_cancel(self._redraw_job); self._redraw_job=None
    def request_redraw(self):
        if self.app.live_preview.get() and self._redraw_job is None: self._redraw_job=self.after(120,self.redraw)


class StudioApp(PainterApp):
    def __init__(self,session):
        self.session=session; self.drawing=Drawing(); self.mesh=compile_surface(self.drawing)
        self.pending=0; self.sent_at=0.; self.connected=False; self.draft_dirty=False; self.project_path=None
        self.geometry_undo=deque(maxlen=128); self.geometry_redo=deque(maxlen=128)
        super().__init__()
        self.title("A:M Patch Draw Studio 0.2"); self.geometry(f"{min(1280,max(1060,self.winfo_screenwidth()-80))}x{min(820,max(660,self.winfo_screenheight()-100))}"); self.minsize(1060,660)
        self.image=Image.new("RGB",(1024,1024),(210,210,210)); self.erase_baseline=self.image.copy()
        self.projection.set("Oblique"); self.side_filter.set("All"); self.tool.set("brush")
        self.show_labels.set(False); self.patch_only.set(True)
        for var in [*self.fields.values(),self.shape_name,self.native_smooth,self.round_outline]:
            var.trace_add("write",lambda *args:setattr(self,"draft_dirty",True))
        self.rebuild(); self.after(500,self.poll_receiver)
        self.status.set("Launch the A:M receiver on your destination model, then select the connection file shown above.")

    def _build_menu(self):
        menu=tk.Menu(self); file=tk.Menu(menu,tearoff=False)
        file.add_command(label="Open Draft...",command=self.open_project)
        file.add_command(label="Save Draft As...",command=self.save_project)
        file.add_separator(); file.add_command(label="Export Paint Image As...",command=self.save_texture_as)
        file.add_command(label="Resize Draft Texture...",command=self.resize_texture)
        file.add_command(label="Clear Draft Paint...",command=self.clear_paint)
        file.add_separator(); file.add_command(label="Close Studio",command=self.close)
        menu.add_cascade(label="File",menu=file)
        edit=tk.Menu(menu,tearoff=False)
        edit.add_command(label="Undo active tab",command=self.context_undo)
        edit.add_command(label="Redo active tab",command=self.context_redo)
        edit.add_command(label="Set current paint as erase baseline",command=self.set_erase_baseline)
        menu.add_cascade(label="Edit",menu=edit)
        help_menu=tk.Menu(menu,tearoff=False)
        help_menu.add_command(label="Workflow and limits",command=self.show_help)
        menu.add_cascade(label="Help",menu=help_menu); self.config(menu=menu)

    def _build_ui(self):
        top=ttk.Frame(self,padding=8); top.pack(fill="x")
        self.target=tk.StringVar(value="A:M: not connected")
        ttk.Label(top,textvariable=self.target).pack(side="left")
        ttk.Button(top,text="Copy connection path",command=lambda:self.copy_connection()).pack(side="right")
        connection=ttk.Entry(self); connection.insert(0,str(self.session.connection)); connection.configure(state="readonly"); connection.pack(fill="x",padx=8)
        sendrow=ttk.Frame(self,padding=8); sendrow.pack(fill="x")
        ttk.Label(sendrow,text="Shape/group name").pack(side="left")
        self.shape_name=tk.StringVar(value=self.drawing.name)
        ttk.Entry(sendrow,textvariable=self.shape_name,width=27).pack(side="left",padx=6)
        self.include_paint=tk.BooleanVar(value=True)
        ttk.Checkbutton(sendrow,text="Include a paint snapshot",variable=self.include_paint).pack(side="left",padx=6)
        self.send_button=ttk.Button(sendrow,text="Send to A:M",command=self.send_snapshot,state="disabled"); self.send_button.pack(side="right")
        ttk.Button(sendrow,text="Save Draft...",command=self.save_project).pack(side="right",padx=8)
        self.last_send=tk.StringVar(value="No shape sent in this session.")
        ttk.Label(self,textvariable=self.last_send,anchor="w",padding=(5,2),wraplength=1100).pack(side="bottom",fill="x")
        self.footer=ttk.Label(self,textvariable=self.status,relief="sunken",anchor="w",padding=5,wraplength=1100)
        self.footer.pack(side="bottom",fill="x")
        self.tabs=ttk.Notebook(self); self.tabs.pack(fill="both",expand=True,padx=8)
        drawing=ttk.Frame(self.tabs); paint=ttk.Frame(self.tabs)
        self.tabs.add(drawing,text="1  Draw and shape"); self.tabs.add(paint,text="2  Patch paint")
        self.statistics=tk.StringVar()
        ttk.Label(drawing,textvariable=self.statistics,justify="left",wraplength=1000,padding=5).pack(side="bottom",fill="x")
        self.draw_tool=tk.StringVar(value="Draw"); self.draw_brush=tk.StringVar(value="1")
        controls=ttk.Frame(drawing,padding=5); controls.pack(fill="x")
        for label in ("Draw","Erase"):
            ttk.Radiobutton(controls,text=label,value=label,variable=self.draw_tool).pack(side="left")
        ttk.Label(controls,text="Brush (cells)").pack(side="left",padx=(15,3))
        ttk.Combobox(controls,values=("0.5","1","2","4","8"),textvariable=self.draw_brush,width=5,state="readonly").pack(side="left")
        for label,command in (("Undo",self.geometry_back),("Redo",self.geometry_forward),("Clear",self.clear_geometry),("Fit",lambda:self.draw_canvas.fit())):
            ttk.Button(controls,text=label,command=command,width=7).pack(side="left",padx=4)
        ttk.Button(controls,text="Ring test",command=lambda:self.preset("ring")).pack(side="right")
        ttk.Button(controls,text="Full sheet",command=lambda:self.preset("sheet")).pack(side="right",padx=5)
        body=ttk.Frame(drawing); body.pack(fill="both",expand=True)
        self.draw_canvas=DrawCanvas(body,self); self.draw_canvas.pack(side="left",fill="both",expand=True)
        sideframe=ttk.Frame(body); sideframe.pack(side="right",fill="y")
        sidecanvas=tk.Canvas(sideframe,width=278,highlightthickness=0)
        scrollbar=ttk.Scrollbar(sideframe,orient="vertical",command=sidecanvas.yview); scrollbar.pack(side="right",fill="y")
        sidecanvas.configure(yscrollcommand=scrollbar.set); sidecanvas.pack(side="left",fill="both",expand=True)
        sidebar=ttk.Frame(sidecanvas,padding=10); sidecanvas.create_window((0,0),window=sidebar,anchor="nw")
        sidebar.bind("<Configure>",lambda e:sidecanvas.configure(width=sidebar.winfo_reqwidth(),scrollregion=sidecanvas.bbox("all")))
        self.fields={}
        def field(label,key,value,values=None):
            row=ttk.Frame(sidebar); row.pack(fill="x",pady=5)
            ttk.Label(row,text=label,width=15).pack(side="left"); var=tk.StringVar(value=str(value)); self.fields[key]=var
            widget=ttk.Combobox(row,values=values,textvariable=var,state="readonly",width=13) if values else ttk.Entry(row,textvariable=var,width=15)
            widget.pack(side="right",fill="x",expand=True)
        field("Grid resolution","side",16,(3,4,8,16,32,64))
        ttk.Button(sidebar,text="Refine x2 (same world size)",command=self.refine).pack(fill="x",pady=4)
        field("Width (units)","width",100); field("Height","height",100)
        field("Surface profile","surface","Flat",SURFACES); field("Rise (units)","rise",15)
        field("Plane","plane","XY",("XY","XZ","YZ"))
        field("Origin X, Y, Z","origin","0, 0, 0")
        self.native_smooth=tk.BooleanVar(value=True); self.round_outline=tk.BooleanVar(value=False)
        ttk.Checkbutton(sidebar,text="Native Smooth splines",variable=self.native_smooth).pack(anchor="w",pady=(8,1))
        ttk.Checkbutton(sidebar,text="Soften draft outline",variable=self.round_outline).pack(anchor="w")
        ttk.Button(sidebar,text="Apply shape settings",command=self.apply_settings).pack(fill="x",pady=8)
        toolbar=ttk.Frame(paint,padding=5); toolbar.pack(fill="x")
        for label,value in (("Select","select"),("Brush","brush"),("Eraser","eraser"),("Picker","picker")):
            ttk.Radiobutton(toolbar,text=label,value=value,variable=self.tool,command=self._tool_changed).pack(side="left")
        self.color_button=tk.Button(toolbar,text="Color",command=self.choose_color,width=7); self.color_button.pack(side="left",padx=4)
        toolbar=ttk.Frame(paint,padding=(5,0,5,5)); toolbar.pack(fill="x")
        ttk.Label(toolbar,text="Pixels").pack(side="left",padx=(8,0)); ttk.Scale(toolbar,from_=1,to=200,variable=self.brush_size,length=100).pack(side="left")
        ttk.Label(toolbar,text="Opacity").pack(side="left"); ttk.Scale(toolbar,from_=1,to=100,variable=self.opacity,length=80).pack(side="left")
        ttk.Button(toolbar,text="Fill patch",command=self.fill_selected_patch).pack(side="left")
        ttk.Checkbutton(toolbar,text="One patch",variable=self.patch_only).pack(side="left",padx=5)
        ttk.Button(toolbar,text="Undo",command=self.undo).pack(side="right"); ttk.Button(toolbar,text="Redo",command=self.redo).pack(side="right")
        panes=ttk.Panedwindow(paint,orient="horizontal"); panes.pack(fill="both",expand=True)
        atlas=ttk.Labelframe(panes,text="Paint texture / patch selection (wheel zoom, middle drag pan)")
        self.texture_canvas=StudioTextureCanvas(atlas,self); self.texture_canvas.pack(fill="both",expand=True); panes.add(atlas,weight=3)
        right=ttk.Frame(panes); panes.add(right,weight=2)
        viewbar=ttk.Frame(right); viewbar.pack(fill="x")
        views=ttk.Combobox(viewbar,values=("Oblique","Front (X-Y)","Side (Z-Y)","Top (Z-X)"),textvariable=self.projection,state="readonly",width=15)
        self.live_preview=tk.BooleanVar(value=True)
        ttk.Checkbutton(viewbar,text="Live",variable=self.live_preview,command=lambda:self.model_canvas.request_redraw()).pack(side="right")
        ttk.Button(viewbar,text="Update preview",command=lambda:self.model_canvas.render_now()).pack(side="right")
        views.pack(side="left"); views.bind("<<ComboboxSelected>>",lambda e:self.model_canvas.request_redraw())
        ttk.Checkbutton(viewbar,text="Edges",variable=self.show_outlines,command=self.refresh_views).pack(side="left")
        ttk.Label(right,text="Corner-triangle paint preview; A:M evaluates the actual curved patches.",wraplength=430).pack(fill="x")
        self.model_canvas=StudioModelCanvas(right,self); self.model_canvas.pack(fill="both",expand=True)
        self.patch_tree=ttk.Treeview(right,columns=("patch","topology","groups","side"),show="headings",height=4)
        for key,title in (("patch","Patch"),("topology","CPs"),("groups","Draft group"),("side","Side")):
            self.patch_tree.heading(key,text=title); self.patch_tree.column(key,width=70 if key!="groups" else 170)
        self.patch_tree.pack(fill="x"); self.patch_tree.bind("<<TreeviewSelect>>",self._tree_selected)
        ttk.Label(right,textvariable=self.patch_info,wraplength=420).pack(fill="x")
        self.channel_combo=ttk.Combobox(self)  # Kept for inherited painter compatibility; not displayed.
        self.tabs.bind("<<NotebookTabChanged>>",lambda e:self.tab_changed())

    def _bind_shortcuts(self):
        self.bind("<Control-s>",lambda e:self.save_project()); self.bind("<Control-z>",lambda e:self.context_undo())
        self.bind("<Control-y>",lambda e:self.context_redo())
    def _update_title(self):
        self.title("A:M Patch Draw Studio 0.2 - draft (sent groups are independent)")
    def show_help(self):
        messagebox.showinfo("Patch Draw Studio", "Draw coverage, Apply shape settings, then paint in the second tab.\n\nConnect once from your destination model in A:M. Send creates a new uniquely named native group and an immutable texture snapshot. The Studio stays open; previously sent geometry is not replaced.\n\nNative Smooth is real A:M smoothing. This Python preview uses patch corners, not the A:M evaluator. Refine preserves world size and paint UVs. Draw undo and Paint undo are separate from A:M undo. Save Draft preserves both.\n\nKeep the session folder: A:M references the snapshot PNGs there. Textures are NOT embedded in the HXT or deleted when closing. Move/copy them with your A:M project.\n\nNo live editing of previously sent meshes, hooks, five-point patches or existing-model texture import is performed.",parent=self)
    def copy_connection(self):
        self.clipboard_clear(); self.clipboard_append(str(self.session.connection)); self.status.set("Connection path copied; paste it into the A:M receiver's file chooser")
    def finish_paint_strokes(self):
        if hasattr(self,"texture_canvas"): self.texture_canvas._left_release(None)
        if hasattr(self,"model_canvas"): self.model_canvas._left_release(None)
    def undo(self):
        self.finish_paint_strokes(); super().undo(); self.draft_dirty=True
    def redo(self):
        self.finish_paint_strokes(); super().redo(); self.draft_dirty=True
    def tab_changed(self):
        self.finish_paint_strokes()
        if hasattr(self,"draw_canvas"): self.draw_canvas.cancel()
        if hasattr(self,"texture_canvas"): self.texture_canvas.fit_image(); self.model_canvas.request_redraw()
    def update_fields(self):
        for key in self.fields:
            value=getattr(self.drawing,key); self.fields[key].set(", ".join(str(v) for v in value) if key=="origin" else str(value))
        self.shape_name.set(self.drawing.name); self.native_smooth.set(self.drawing.smooth); self.round_outline.set(self.drawing.round_outline)
    def apply_settings(self):
        try:
            if self.draw_canvas.before is not None: return False
            draft=deepcopy(self.drawing); n=int(self.fields["side"].get())
            if n!=draft.side and draft.cells:
                raise ValueError("Use Refine x2 to preserve a drawing. Clear before choosing a different grid resolution.")
            draft.side=n; draft.width=float(self.fields["width"].get()); draft.height=float(self.fields["height"].get())
            draft.surface=self.fields["surface"].get(); draft.rise=float(self.fields["rise"].get()); draft.plane=self.fields["plane"].get()
            draft.origin=tuple(float(v.strip()) for v in self.fields["origin"].get().split(","))
            draft.smooth=self.native_smooth.get(); draft.round_outline=self.round_outline.get(); draft.name=self.shape_name.get().strip()
            draft.validate(); self.drawing=draft; self.draft_dirty=True; self.rebuild(); return True
        except (ValueError,TypeError) as exc:
            messagebox.showerror("Shape settings",str(exc),parent=self); return False
    def rebuild(self):
        self.finish_paint_strokes()
        try:
            self.mesh=compile_surface(self.drawing)
            cps={i:ControlPoint(i,False,position=tuple(p)) for i,p in enumerate(self.mesh["points"])}
            group="PD_"+self.drawing.name
            patches=[Patch(i,0,f,f,[tuple(self.mesh["points"][j]) for j in f],4,
                           uv_polygon=[tuple(self.mesh["uvs"][j]) for j in f],groups=[group]) for i,f in enumerate(self.mesh["faces"])]
            self.model=StudioBakeModel(self.session.path/"draft-preview",cps,patches,{group:set(cps)},[],"Patch Draw","Generated grid UVs")
            self.model.grid_side=self.drawing.side; self.model.cell_index={cell:i for i,cell in enumerate(self.mesh["face_cells"])}
            self.selected_patch=None; self.patch_masks.clear(); self.patch_info.set("Choose a patch in either paint view")
            self.populate_patch_list(); self.draw_canvas.redraw()
            n=len(patches)
            if n>2048: self.show_outlines.set(False)
            if n>4096: self.live_preview.set(False)
            self.statistics.set(f"{self.drawing.side} x {self.drawing.side} cells | {n:,} quads | {len(cps):,} logical CPs | {len(self.mesh['splines']):,} splines | {self.mesh['occurrences']:,} CP records\n{self.mesh['component_count']} components; {self.mesh['holes']} holes. Curves are evaluated in A:M; texture resolution is independent.")
            if self.tabs.index(self.tabs.select())==1: self.refresh_views()
            self.status.set("Draft ready. Send makes a new group; it never replaces a previous send.")
        except (ValueError,MemoryError) as exc:
            self.mesh={}; self.send_button.configure(state="disabled"); self.status.set("Draft cannot be sent: "+str(exc))
    def populate_patch_list(self):
        if not hasattr(self,"patch_tree") or self.model is None: return
        self.patch_tree.delete(*self.patch_tree.get_children())
        for p in self.model.patches[:2048]:
            self.patch_tree.insert("","end",iid=str(p.index),values=(f"P{p.index:05d}",4,", ".join(p.groups),""))
    def _tree_selected(self,event):
        selected=self.patch_tree.selection()
        if selected:
            index=int(selected[0])
            if index!=self.selected_patch: self.set_selected_patch(index)
    def set_selected_patch(self,index):
        if self.model is None or not 0<=index<len(self.model.patches): return
        self.selected_patch=index; p=self.model.patches[index]
        self.patch_info.set(f"P{index:05d} | {self.drawing.name} | UV {p.uv_bounds}")
        if self.patch_tree.exists(str(index)): self.patch_tree.selection_set(str(index)); self.patch_tree.see(str(index))
        self.texture_canvas.request_redraw()
        if self.live_preview.get(): self.model_canvas.request_redraw()
    def get_patch_mask(self,index):
        if self.image is None or self.model is None: raise ValueError("No paint draft")
        key=(index,self.image.size)
        if key not in self.patch_masks:
            if len(self.patch_masks)>=4: self.patch_masks.pop(next(iter(self.patch_masks)))
            self.patch_masks[key]=self.model.patch_mask(index,self.image.size)
        return self.patch_masks[key]
    def begin_edit(self):
        if self.image is None: return
        self.undo_stack.append(self.image.copy()); self.redo_stack.clear()
        limit=max(1,min(32,(48*1024*1024)//(self.image.width*self.image.height*4)))
        del self.undo_stack[:-limit]
    def finish_edit(self):
        super().finish_edit(); self.draft_dirty=True
    def context_undo(self):
        if self.tabs.index(self.tabs.select())==0: self.geometry_back()
        else: self.undo()
    def context_redo(self):
        if self.tabs.index(self.tabs.select())==0: self.geometry_forward()
        else: self.redo()
    def geometry_back(self):
        self.draw_canvas.cancel()
        if self.geometry_undo:
            self.geometry_redo.append(set(self.drawing.cells)); self.drawing.cells=self.geometry_undo.pop(); self.draft_dirty=True; self.rebuild()
    def geometry_forward(self):
        self.draw_canvas.cancel()
        if self.geometry_redo:
            self.geometry_undo.append(set(self.drawing.cells)); self.drawing.cells=self.geometry_redo.pop(); self.draft_dirty=True; self.rebuild()
    def clear_geometry(self):
        self.draw_canvas.cancel()
        if self.drawing.cells:
            self.geometry_undo.append(set(self.drawing.cells)); self.geometry_redo.clear(); self.drawing.cells.clear(); self.draft_dirty=True; self.rebuild()
    def refine(self):
        try:
            self.draw_canvas.cancel(); self.drawing.refine(); self.geometry_undo.clear(); self.geometry_redo.clear()
            self.update_fields(); self.draft_dirty=True; self.rebuild()
            self.status.set("Resolution doubled; world size and paint preserved. Drawing undo history reset.")
        except ValueError as exc: messagebox.showinfo("Refine",str(exc),parent=self)
    def preset(self,kind):
        if self.drawing.cells and not messagebox.askyesno("Replace draft coverage?","Replace coverage? Existing paint is retained, and A:M groups are unaffected.",parent=self): return
        self.draw_canvas.cancel(); self.geometry_undo.append(set(self.drawing.cells)); self.geometry_redo.clear()
        n=self.drawing.side
        self.drawing.cells={(x,y) for y in range(n) for x in range(n) if kind=="sheet" or not(n//3<=x<2*n//3 and n//3<=y<2*n//3)}
        self.draft_dirty=True; self.rebuild()
    def refresh_views(self):
        if hasattr(self,"tabs") and self.tabs.index(self.tabs.select())!=1: return
        self.texture_canvas.request_redraw()
        if self.live_preview.get(): self.model_canvas.request_redraw()
    def clear_paint(self):
        if messagebox.askyesno("Clear draft paint?","Reset only draft paint to neutral gray? Sent textures stay unchanged.",parent=self):
            self.begin_edit(); self.image.paste((210,210,210),(0,0,*self.image.size)); self.finish_edit(); self.refresh_views()
    def resize_texture(self):
        from tkinter.simpledialog import askinteger
        n=askinteger("Draft texture resolution","Pixels per side: 256, 512, 1024 or 2048",initialvalue=self.image.width,parent=self)
        if n is None: return
        if n not in (256,512,1024,2048): messagebox.showerror("Texture","Choose 256, 512, 1024 or 2048",parent=self); return
        if not messagebox.askyesno("Resize paint?","Resample draft paint and reset paint undo history?",parent=self): return
        self.image=self.image.resize((n,n),Image.Resampling.LANCZOS); self.erase_baseline=self.erase_baseline.resize((n,n),Image.Resampling.LANCZOS)
        self.undo_stack.clear(); self.redo_stack.clear(); self.patch_masks.clear(); self.draft_dirty=True; self.dirty=True; self.refresh_views()
    def save_texture(self):
        # Never write back over a previously sent immutable native texture.
        return self.save_texture_as()
    def save_texture_as(self):
        if self.image is None: return False
        path=filedialog.asksaveasfilename(title="Export draft paint (not a live A:M update)",defaultextension=".png",filetypes=[("PNG","*.png")],parent=self)
        if not path: return False
        if Path(path).resolve().parent==self.session.path:
            messagebox.showerror("Reserved workspace","Save exported paint outside the transfer workspace; sent textures are immutable.",parent=self); return False
        try: self.image.save(path); self.status.set("Paint exported; Save Draft also preserves drawing settings."); return True
        except OSError as exc: messagebox.showerror("Save paint",str(exc),parent=self); return False
    def save_project(self):
        if not self.apply_settings(): return False
        path=filedialog.asksaveasfilename(title="Save complete drawing and paint draft",defaultextension=".patchdraw",filetypes=[("Patch Draw draft","*.patchdraw")],parent=self)
        if not path: return False
        target=Path(path); temp=target.with_name(target.name+".tmp-"+self.session.token)
        created=False
        try:
            with temp.open("xb") as out:
                created=True
                with zipfile.ZipFile(out,"w",zipfile.ZIP_DEFLATED) as z:
                    z.writestr("recipe.json",json.dumps(self.drawing.recipe(),allow_nan=False))
                    image=io.BytesIO(); self.image.save(image,format="PNG"); z.writestr("paint.png",image.getvalue())
                out.flush(); os.fsync(out.fileno())
            os.replace(temp,target); self.project_path=target; self.draft_dirty=False; self.dirty=False; self.status.set("Saved draft: "+str(target)); return True
        except (OSError,ValueError) as exc: messagebox.showerror("Save draft",str(exc),parent=self); return False
        finally:
            if created: temp.unlink(missing_ok=True)
    def open_project(self):
        if not self.confirm_discard_changes(): return
        path=filedialog.askopenfilename(filetypes=[("Patch Draw draft","*.patchdraw")],parent=self)
        if not path: return
        try:
            with zipfile.ZipFile(path) as z:
                info=z.infolist()
                if len(info)!=2 or {i.filename for i in info}!={"recipe.json","paint.png"} or sum(i.file_size for i in info)>24*1024*1024: raise ValueError("Unsupported/oversized draft archive")
                drawing=Drawing.from_recipe(strict_json(z.read("recipe.json").decode("utf-8")))
                with Image.open(io.BytesIO(z.read("paint.png"))) as image:
                    if image.format!="PNG" or image.width!=image.height or image.width not in (256,512,1024,2048): raise ValueError("Invalid draft PNG dimensions")
                    image.load(); paint=image.convert("RGB")
            compile_surface(drawing)  # Validate before replacing the working draft.
            self.drawing=drawing; self.image=paint; self.erase_baseline=paint.copy(); self.undo_stack.clear(); self.redo_stack.clear()
            self.geometry_undo.clear(); self.geometry_redo.clear(); self.update_fields(); self.rebuild(); self.project_path=Path(path); self.draft_dirty=False; self.dirty=False
        except (OSError,ValueError,KeyError,zipfile.BadZipFile) as exc: messagebox.showerror("Open draft",str(exc),parent=self)
    def confirm_discard_changes(self):
        if not(self.draft_dirty or self.dirty): return True
        answer=messagebox.askyesnocancel("Save draft?","Save drawing and paint before closing/replacing the draft? Sent A:M shapes are independent.",parent=self)
        return False if answer is None else self.save_project() if answer else True
    def send_snapshot(self):
        if self.pending or not self.connected: return
        if not self.apply_settings() or not self.mesh.get("faces"): return
        try:
            if (self.session.path/"request.json").exists() or (self.session.path/"processing.json").exists(): raise ValueError("A request is already pending; inspect the receiver before sending again")
            serial=self.session.serial+1; texture=f"paint-{self.session.token}-{serial:06d}.png" if self.include_paint.get() else ""
            plan=self.session.packet(self.drawing,self.mesh,texture)
            if texture:
                with (self.session.path/texture).open("xb") as f:
                    self.image.save(f,format="PNG"); f.flush(); os.fsync(f.fileno())
            atomic_json(self.session.path/"request.json",plan,replace=False)
            self.pending=plan["serial"]; self.sent_at=time.monotonic(); self.send_button.configure(state="disabled"); self.status.set("Snapshot queued. Confirm the destination in A:M; the submitted snapshot is independent of later draft edits.")
        except (OSError,ValueError) as exc: messagebox.showerror("Send",str(exc),parent=self)
    def read_status(self,path):
        with path.open("rb") as f: raw=f.read(16385)
        if len(raw)>16384: raise ValueError("Oversized receiver status")
        result=strict_json(raw.decode("utf-8"))
        if not isinstance(result,dict): raise ValueError("Invalid receiver status")
        return result
    def poll_receiver(self):
        try:
            state_path=self.session.path/"receiver.json"
            state=self.read_status(state_path) if state_path.exists() else {}
            self.connected=(state.get("session")==self.session.token and state.get("status")=="connected" and abs(time.time()*1000-state.get("updated",0))<3500)
            label="A:M target: "+state.get("target","") if self.connected else "A:M: disconnected / paused (draft is safe)"
            self.target.set(label)
            result_path=self.session.path/"result.json"
            if self.pending and result_path.exists():
                result=self.read_status(result_path)
                if (result.get("session")==self.session.token and type(result.get("serial")) is int and
                        result["serial"] in (0,self.pending) and result.get("status") in ("ok","failed") and isinstance(result.get("message"),str)):
                    self.pending=0
                    self.status.set(result.get("message","Receiver completed"))
                    self.last_send.set(result.get("message","Receiver completed").split("\n")[0])
                    if result.get("status")!="ok": messagebox.showwarning("A:M send",result.get("message","Send failed. Inspect A:M before retrying."),parent=self)
            self.send_button.configure(state="normal" if self.connected and not self.pending and self.mesh.get("faces") else "disabled")
        except (OSError,ValueError,TypeError):
            self.connected=False; self.target.set("A:M: connection status unavailable"); self.send_button.configure(state="disabled")
        self.after(500,self.poll_receiver)
    def close(self):
        if self.pending and not self.connected and time.monotonic()-self.sent_at>10:
            if not messagebox.askyesno("Unacknowledged send", "The receiver is unavailable. Close Studio while retaining all transfer files? The send may have changed A:M. Inspect the model before any retry.",parent=self): return
        elif self.pending:
            messagebox.showwarning("Send pending","Wait for A:M's response. To preserve a draft before resolving an interrupted send, use Save Draft. Never resend an unacknowledged request blindly.",parent=self); return
        if self.confirm_discard_changes(): self.destroy()


def main():
    parser=argparse.ArgumentParser(description="A:M Patch Draw Studio and QuickDecal Painter")
    parser.add_argument("--workspace",type=Path,help="Existing parent folder for a fresh persistent session")
    parser.add_argument("--smoke-test",action="store_true",help=argparse.SUPPRESS)
    args=parser.parse_args()
    if args.workspace is None:
        root=tk.Tk(); root.withdraw()
        path=filedialog.askdirectory(title="Choose a persistent folder beside your A:M project (paint snapshots must be kept)",parent=root)
        root.destroy()
        if not path: return 0
        args.workspace=Path(path)
    session=Session(args.workspace.resolve())
    app=StudioApp(session)
    if args.smoke_test:
        app.preset("sheet"); app.tabs.select(1); app.update(); app.set_selected_patch(0); app.fill_selected_patch()
        app.after(300,app.destroy)
    app.mainloop(); return 0


if __name__=="__main__":
    raise SystemExit(main())
