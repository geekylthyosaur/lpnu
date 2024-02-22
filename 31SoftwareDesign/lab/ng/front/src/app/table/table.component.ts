import { Component, OnInit } from '@angular/core';
import { DataService } from '../data.service';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-table',
  standalone: true,
  templateUrl: './table.component.html',
  styleUrls: ['./table.component.css'],
  imports: [CommonModule],
})
export class TableComponent implements OnInit {
  items: any[] = [];

  constructor(private dataService: DataService) { }

  ngOnInit(): void {
    this.loadData();
  }

  loadData(): void {
    this.dataService.getData().subscribe(
      (data: any[]) => {
        console.log(data);
        this.items = data;
      },
      (error) => {
        console.error('Error fetching data:', error);
      }
    );
  }

  deleteItem(itemId: number): void {
    this.items = this.items.filter(item => item.id !== itemId);
  }
}