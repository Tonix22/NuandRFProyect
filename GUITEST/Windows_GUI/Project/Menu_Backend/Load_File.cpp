#include "my_mainwindow.h"


/**************************************************************
 ************************FILE EXPLORER*************************
 *************************************************************/

/*
get_rx_rssi_num
set_rx_fir_config_num
get_rx_fir_config_num
rx_fastlock_load_num
set_tx_fir_config_num
get_tx_fir_config_num
tx_fastlock_load_num
set_trx_path_clks_num
trx_load_enable_fir_num
*/


void MainWindow ::Special_ones(int id)
{
    QString filter = "Text File (*.txt*) ;; All File (*.*)";
    QString file_name = QFileDialog::getOpenFileName(this,"List of Parameters",QDir::currentPath(),filter);
    QMessageBox::information(this,"struct selected",file_name);
    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"title", "file not open");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    file.close();
}
