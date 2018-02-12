// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include <EditorFramework/Editor.h>
#include <IEditor.h>
#include <SystemTypes.h>

class QAction;
class QLabel;
class QToolBar;
class QVBoxLayout;

namespace ACE
{
class CSystemAssetsManager;
class CSystemControlsWidget;
class CPropertiesWidget;
class CMiddlewareDataWidget;
class CSystemAsset;
class CSystemControl;
class CFileMonitorSystem;
class CFileMonitorMiddleware;

class CMainWindow final : public CDockableEditor, public IEditorNotifyListener
{
	Q_OBJECT

public:

	CMainWindow();
	virtual ~CMainWindow() override;

	// CDockableEditor
	virtual char const* GetEditorName() const override { return "Audio Controls Editor"; }
	// ~CDockableEditor

	// IEditorNotifyListener
	virtual void OnEditorNotifyEvent(EEditorNotifyEvent event) override;
	// ~IEditorNotifyListener

	// IPane
	virtual IViewPaneClass::EDockingDirection GetDockingDirection() const override { return IViewPaneClass::DOCK_FLOAT; }
	// ~IPane

protected:

	// QWidget
	virtual void keyPressEvent(QKeyEvent* pEvent) override;
	virtual void closeEvent(QCloseEvent* pEvent) override;
	// ~QWidget

	// CEditor
	virtual void CreateDefaultLayout(CDockableContainer* pSender) override;
	virtual bool CanQuit(std::vector<string>& unsavedChanges) override;
	// ~CEditor

protected slots:

	void OnSystemControlsWidgetDestruction(QObject* const pObject);
	void OnPropertiesWidgetDestruction(QObject* const pObject);
	void OnMiddlewareDataWidgetDestruction(QObject* const pObject);

signals:

	void SignalSelectedSystemControlChanged();
	void SignalSelectConnectedSystemControl(CSystemControl& systemControl, CID const itemId);
	void SignalSelectConnectedImplItem(CID const itemId);

private slots:

	void OnPreferencesDialog();

private:

	void                       InitMenuBar();
	void                       InitToolbar(QVBoxLayout* const pWindowLayout);
	void                       UpdateImplLabel();
	void                       RegisterWidgets();
	void                       Reload();
	void                       Save();
	void                       SaveBeforeImplementationChange();
	void                       CheckErrorMask();
	void                       UpdateAudioSystemData();
	void                       ReloadSystemData();
	void                       ReloadMiddlewareData();
	void                       RefreshAudioSystem();
	void                       BackupTreeViewStates();
	void                       RestoreTreeViewStates();
	bool                       TryClose();

	std::vector<CSystemAsset*> GetSelectedSystemAssets();

	CSystemControlsWidget*     CreateSystemControlsWidget();
	CPropertiesWidget*         CreatePropertiesWidget();
	CMiddlewareDataWidget*     CreateMiddlewareDataWidget();

	CSystemAssetsManager* const   m_pAssetsManager;
	CSystemControlsWidget*        m_pSystemControlsWidget;
	CPropertiesWidget*            m_pPropertiesWidget;
	CMiddlewareDataWidget*        m_pMiddlewareDataWidget;
	QToolBar*                     m_pToolBar;
	QAction*                      m_pSaveAction;
	QLabel* const                 m_pImplNameLabel;
	CFileMonitorSystem* const     m_pMonitorSystem;
	CFileMonitorMiddleware* const m_pMonitorMiddleware;
	bool                          m_isModified;
	bool                          m_isReloading;
};
} // namespace ACE
