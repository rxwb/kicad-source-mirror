/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright The KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <wx/button.h>
#include <wx/sizer.h>

#include <dialogs/dialog_embed_files.h>


DIALOG_EMBED_FILES::DIALOG_EMBED_FILES( wxWindow* aParent, const wxString& aTitle ) :
        DIALOG_SHIM( aParent, wxID_ANY, aTitle, wxDefaultPosition, wxDefaultSize,
                     wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER ),
        m_contentPanel( nullptr )
{
    // Construction delayed until after panel is installed
}


void DIALOG_EMBED_FILES::InstallPanel( wxPanel* aPanel )
{
    m_contentPanel = aPanel;

    // Now perform the body of the constructor
    auto mainSizer = new wxBoxSizer( wxVERTICAL );
    SetSizer( mainSizer );

    mainSizer->Add( m_contentPanel, 1, wxEXPAND|wxLEFT|wxTOP|wxRIGHT, 5 );
    m_contentPanel->SetMinSize( FromDIP( wxSize( 1000, 600 ) ) );

    auto sdbSizer = new wxStdDialogButtonSizer();
    auto sdbSizerOK = new wxButton( this, wxID_OK );
    sdbSizer->AddButton( sdbSizerOK );
    auto sdbSizerCancel = new wxButton( this, wxID_CANCEL );
    sdbSizer->AddButton( sdbSizerCancel );
    sdbSizer->Realize();

    mainSizer->Add( sdbSizer, 0, wxALL|wxEXPAND, 5 );

    SetupStandardButtons();

    finishDialogSettings();

    // On some windows manager (Unity, XFCE), this dialog is not always raised, depending
    // on how the dialog is run.
    Raise();
}


bool DIALOG_EMBED_FILES::TransferDataToWindow()
{
    return m_contentPanel->TransferDataToWindow();
}


bool DIALOG_EMBED_FILES::TransferDataFromWindow()
{
    /**
     * N.B. *do not* call wxDialog::TransferDataFromWindow() in the dialog code.
     */
    return m_contentPanel->TransferDataFromWindow();
}

