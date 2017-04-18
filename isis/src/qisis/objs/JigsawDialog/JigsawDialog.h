#ifndef JigsawDialog_h
#define JigsawDialog_h

#include <QDialog>
#include <QPointer>
#include <QWidget>

#include "BundleAdjustWorkOrder.h"
#include "BundleSettings.h"
#include "IException.h"

namespace Ui {
  class JigsawDialog;
}

class QString;

namespace Isis {
  class BundleAdjust;
  class BundleSolutionInfo;
  class Control;
  class Directory;
  class Project;

  /**
   * This dialog allows the user to select the bundle adjust parameters, run the bundle, and view
   * the results.
   *
   * @author 2014-??-?? Ken Edmundson
   *
   * @internal
   *   @history 2014-09-18 Kimberly Oyama - Added code to thread the bundle run. It is currently
   *                           commented out but it works.
   *   @history 2015-02-20 Jeannie Backer - Replaced BundleResults references with
   *                           BundleSolutionInfo and BundleStatistics references with BundleResults
   *                           due to class name changes.
   *   @history 2015-09-03 Jeannie Backer - Modified to create JigsawSetupDialog object using the
   *                           value for the useLastSettings checkbox. When the Run button is
   *                           clicked, the run time will now be used to create a uniquely named
   *                           directory to contain the output files for the bundle solution.
   *   @history 2017-04-17 Ian Humphrey - Added second constructor that can be used when the
   *                           JigsawWorkOrder initially creates a setup dialog so it can pass
   *                           information to this dialog. Added init() delegate method for
   *                           constructors to use to reduce code duplication. Modified
   *                           notifyThreadFinished to update the Run button. References #4748.
   */
  class JigsawDialog : public QDialog {
    Q_OBJECT

  public:
    explicit JigsawDialog(Project *project, QWidget *parent = 0);
    explicit JigsawDialog(Project *project,
                          BundleSettingsQsp bundleSettings,
                          Control *selectedControl,
                          QWidget *parent = 0);

    ~JigsawDialog();

  public slots:
    void outputBundleStatus(QString status);
    void errorString(QString error);
    void reportException(QString exception);
    void updateIterationSigma0(int iteration, double sigma0);
    void bundleFinished(BundleSolutionInfo *bundleSolutionInfo);
    void notifyThreadFinished();

  protected:
    void init();
    BundleAdjust *m_bundleAdjust;
    Project *m_project;
    Control *m_selectedControl;
    QString *m_selectedControlName;
    BundleSettingsQsp m_bundleSettings;

  private:
    bool m_bRunning;

  private slots:
    void on_JigsawSetupButton_pressed();
    void on_JigsawRunButton_clicked();

  private:
    Ui::JigsawDialog *m_ui;
  };
};
#endif
